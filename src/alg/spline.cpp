// spline.cpp
// v-Spline interpolation
// Ref. "v-Quaternion Splines for the Smooth Interpolation of Orientations"
// G.M. Nielson, IEEE Trans. on Vis. and C.G., 10(2), 2004.
// Dec 2005
// celes@tecgraf.puc-rio.br


#include "spline.h"

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

#define TOL  1.0e-3   // geometric tolerance
#define NTOL 1.0e-7   // numerical tolerance


AlgSpline::AlgSpline ()
: m_n(-1), m_nseg(0), m_size(0), m_ind(0), 
	m_P(0), m_R(0), m_L(0), m_t(0), m_v(0),
  m_a(0), m_b(0), m_c(0), m_d(0), m_auto_knot(2), m_def_v(0)
{
}

AlgSpline::~AlgSpline ()
{
  free(m_ind);
  free(m_P);
  free(m_R);
  free(m_L);
  free(m_t);
  free(m_v);
}

void AlgSpline::SetDefaultTension (double v)
{
  m_def_v = v;
}

void AlgSpline::SetAutoKnotMethod (int autoknot)
{
  m_auto_knot = autoknot;
}

void AlgSpline::Begin ()
{
  m_n = -1;
}

void AlgSpline::AddPosition (double x, double y, double z)
{
  ++m_n; Reserve();
  m_P[m_n].x = x, m_P[m_n].y = y, m_P[m_n].z = z;
  m_v[m_n] = m_def_v;
  m_t[m_n] = (double)m_n;         // default: set initial value as uniform
}

void AlgSpline::SetTension (double v)
{
  m_v[m_n] = v;
}

void AlgSpline::SetKnot (double t)
{
  m_t[m_n] = t;
}

bool AlgSpline::End ()
{
  AdjustSize();
  return Recompute();
}

bool AlgSpline::ModifyPosition (int i, double x, double y, double z)
{
  if (i>=0 && i<=m_n) {
    m_P[i].x = x, m_P[i].y = y, m_P[i].z = z;
    return true;
  }
  else
    return false;
}

bool AlgSpline::ModifyKnot (int i, double t)
{
  if (i>=0 && i<=m_n) {
    m_t[i] = t;
    return true;
  }
  else
    return false;
}

bool AlgSpline::ModifyTension (int i, double v)
{
  if (i>=0 && i<=m_n) {
    m_v[i] = v;
    return true;
  }
  else
    return false;
}

bool AlgSpline::Recompute ()
{
  if (m_n < 1)
    return false;
  GenerateKnot();
  EliminateDuplications();
  AllocTemp();
  FillA();
  FillB();
  FillC();
  bool status = SolveD();
  if (status) {
    FillR();
    FillL();
  }
  FreeTemp();
  return status;
}

void AlgSpline::GetPosition (double t, double* x, double* y, double* z)
{
  // find Bezier parametrization (clamping if necessary)
  int i = (int)t;
  if (i<0) {
    i = 0;
    t = 0;
  }
  else if (i>=m_size-1) {
    i = m_size-2;
    t = 1;
  }
  else
   t -= i;

  // access points using indirection
  int i0 = m_ind[i];
  int i1 = m_ind[i+1];

  if (i0 == i1) {
    *x = m_P[i0].x, *y = m_P[i0].y, *z = m_P[i0].z;
    return;
  }
  // compute interpolated position
  Point b0 = Linear(t,m_P[i0],m_R[i0]);
  Point b1 = Linear(t,m_R[i0],m_L[i0]);
  Point b2 = Linear(t,m_L[i0],m_P[i1]);
  b0 = Linear(t,b0,b1);
  b1 = Linear(t,b1,b2);
  b0 = Linear(t,b0,b1);
  *x = b0.x, *y = b0.y, *z = b0.z;
}

int AlgSpline::GetNSegments ()
{
	return m_nseg;
}

int AlgSpline::GetNPositions ()
{
  return m_n+1;
}

void AlgSpline::GetGivenPosition (int i, double* x, double* y, double* z)
{
  assert(i>=0 && i<m_size);
  *x = m_P[m_ind[i]].x;
  *y = m_P[m_ind[i]].y;
  *z = m_P[m_ind[i]].z;
}

double AlgSpline::GetKnot (int i)
{
  assert(i>=0 && i<m_size);
  return m_t[m_ind[i]];
}

double AlgSpline::GetTension (int i)
{
  assert(i>=0 && i<m_size);
  return m_v[m_ind[i]];
}


// PRIVATE METHODS


void AlgSpline::GenerateKnot ()
{
  if (m_auto_knot != 0) {
    m_t[0] = 0;
    int i;
    for (i=1; i<=m_n; ++i)
      m_t[i] = m_t[i-1] + (m_auto_knot==1 ? 1 : Distance(m_P[i],m_P[i-1]));
    // normalize
    double len = m_t[m_n];
    for (i=1; i<=m_n; ++i)
      m_t[i] /= len;
  }
}

void AlgSpline::EliminateDuplications ()
{
  int i = 0;
  int k = 0;
	m_nseg = m_n;
  m_ind[i++] = k++;
  while (i <= m_n) {
    //printf("dist(%d) = %g\n",i,Distance(m_P[i],m_P[i-1]));
    if (Distance(m_P[i],m_P[i-1]) < TOL) {
      // printf("%d eliminated\n",i);
      memmove(&m_P[i],&m_P[i+1],(m_n-i)*sizeof(Point));
      memmove(&m_t[i],&m_t[i+1],(m_n-i)*sizeof(double));
      memmove(&m_v[i],&m_v[i+1],(m_n-i)*sizeof(double));
      m_n--;
      m_ind[k++] = i-1;
    }
    else {
      // printf("%d NOT eliminated: %.20g\n",i, Distance(m_P[i],m_P[i-1]));
      m_ind[k++] = i++;
    }
  }
  //printf("nseg = %d\n",m_n);
}

double AlgSpline::Distance (const AlgSpline::Point& p0, const AlgSpline::Point& p1)
{
  return (double)sqrt((p1.x-p0.x)*(p1.x-p0.x) + 
                     (p1.y-p0.y)*(p1.y-p0.y) + 
                     (p1.z-p0.z)*(p1.z-p0.z)
                    );
}

const AlgSpline::Point& AlgSpline::Linear (double t, const AlgSpline::Point& p0, const AlgSpline::Point& p1)
{
  static Point p;
  p.x = (1-t)*p0.x + t*p1.x;
  p.y = (1-t)*p0.y + t*p1.y;
  p.z = (1-t)*p0.z + t*p1.z;
  return p;
}

void AlgSpline::FillA ()
{
  m_a[0] = 0; // undefined, not used
  m_a[m_n] = 0;
  for (int i=1; i<m_n; ++i)
    m_a[i] = (1-Di(i)) * (1-Li(i));
}
void AlgSpline::FillB ()
{
  m_b[0] = 1;
  m_b[m_n] = 1;
  for (int i=1; i<m_n; ++i)
    m_b[i] = (1-Di(i))*Li(i) + Di(i)*(1-Mi(i));
}
void AlgSpline::FillC ()
{
  m_c[0] = 0;
  m_c[m_n] = 0; // undefined, not used
  for (int i=1; i<m_n; ++i)
    m_c[i] = Di(i)*Mi(i);
}
// Solve tridiagonal system
// Ref. Numerical Recipes
bool AlgSpline::SolveD ()
{
  int i;
  int n = m_n+1;
  double bet;
  double* a = m_a;
  double* b = m_b;
  double* c = m_c;
  Point* r = m_P;
  Point* u = m_d;

  if (fabs(b[0]) < NTOL)
    return false;

  double* gam = (double*) malloc(n*sizeof(double));  // temp workspace
  bet = b[0];
  u[0].x = r[0].x/bet;
  u[0].y = r[0].y/bet;
  u[0].z = r[0].z/bet;
  for (i=1; i<n; ++i) {
    gam[i] = c[i-1]/bet;
    bet = b[i]-a[i]*gam[i];
    if (fabs(bet) < NTOL) {
      free(gam);
      return false;
    }
    u[i].x = (r[i].x - a[i]*u[i-1].x) / bet;
    u[i].y = (r[i].y - a[i]*u[i-1].y) / bet;
    u[i].z = (r[i].z - a[i]*u[i-1].z) / bet;
  }
  for (i=n-2; i>=0; --i) {
    u[i].x -= gam[i+1] * u[i+1].x;
    u[i].y -= gam[i+1] * u[i+1].y;
    u[i].z -= gam[i+1] * u[i+1].z;
  }
  free(gam);
  return true;
}
void AlgSpline::FillR ()
{
  for (int i=0; i<m_n; ++i) {
    m_R[i].x = (1-Mi(i))*m_d[i].x + Mi(i)*m_d[i+1].x;
    m_R[i].y = (1-Mi(i))*m_d[i].y + Mi(i)*m_d[i+1].y;
    m_R[i].z = (1-Mi(i))*m_d[i].z + Mi(i)*m_d[i+1].z;
  }
}
void AlgSpline::FillL ()
{
  for (int i=0; i<m_n; ++i) {
    m_L[i].x = (1-Li(i+1))*m_d[i].x + Li(i+1)*m_d[i+1].x;
    m_L[i].y = (1-Li(i+1))*m_d[i].y + Li(i+1)*m_d[i+1].y;
    m_L[i].z = (1-Li(i+1))*m_d[i].z + Li(i+1)*m_d[i+1].z;
  }
}
void AlgSpline::Reserve ()
{
  if (m_size <= m_n+1) {
    m_size = m_size==0 ? 4 : 2*m_size;
    m_ind = (int*) realloc(m_ind,m_size*sizeof(int));
    m_P = (Point*) realloc(m_P,m_size*sizeof(Point));
    m_R = (Point*) realloc(m_R,(m_size-1)*sizeof(Point));
    m_L = (Point*) realloc(m_L,(m_size-1)*sizeof(Point));
    m_t = (double*) realloc(m_t,m_size*sizeof(double));
    m_v = (double*) realloc(m_v,m_size*sizeof(double));
  }
}
void AlgSpline::AdjustSize ()
{
  m_size = m_n+1;
  if (m_size)
  {
    m_ind = (int*) realloc(m_ind,m_size*sizeof(int));
    m_P = (Point*) realloc(m_P,m_size*sizeof(Point));
    m_R = (Point*) realloc(m_R,(m_size-1)*sizeof(Point));
    m_L = (Point*) realloc(m_L,(m_size-1)*sizeof(Point));
    m_t = (double*) realloc(m_t,m_size*sizeof(double));
    m_v = (double*) realloc(m_v,m_size*sizeof(double));
  }
}

void AlgSpline::AllocTemp ()
{
  m_a = (double*) malloc(m_size*sizeof(double));
  m_b = (double*) malloc(m_size*sizeof(double));
  m_c = (double*) malloc(m_size*sizeof(double));
  m_d = (Point*) malloc(m_size*sizeof(Point));
}
void AlgSpline::FreeTemp ()
{
  free(m_a);
  free(m_b);
  free(m_c);
  free(m_d);
}

void AlgSpline::Debug ()
{
  int i;
  for (i=0; i<m_n; ++i) {
    printf("P[%d]: %g %g %g\n",i,m_P[i].x,m_P[i].y,m_P[i].z);
    printf("R[%d]: %g %g %g\n",i,m_R[i].x,m_R[i].y,m_R[i].z);
    printf("L[%d]: %g %g %g\n",i,m_L[i].x,m_L[i].y,m_L[i].z);
  }
  printf("P[%d]: %g %g %g\n",m_n,m_P[m_n].x,m_P[m_n].y,m_P[m_n].z);

  for (i=0; i<=m_n; ++i)
    printf("t[%d]: %g\n",i,m_t[i]);
  for (i=0; i<=m_n; ++i)
    printf("v[%d]: %g\n",i,m_v[i]);
}


