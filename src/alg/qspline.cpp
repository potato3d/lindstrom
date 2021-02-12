// qspline.cpp
// v-Orientationernion spline interpolation
// Ref. "v-Orientationernion Orientationernions for the Smooth Interpolation of Orientations"
// G.M. Nielson, IEEE Trans. on Vis. and C.G., 10(2), 2004.
// Dec 2005
// celes@tecgraf.puc-rio.br


#include "qspline.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define TOL 1.0e-5f       // geometric tolerance
#define NTOL 1.0e-10f     // numeric tolerance
#define KMAX 20           // maximun number of iterations

#define PI 3.14159f
#define TORAD(a) ((a)*PI/180)
#define TODEG(a) ((a)*180/PI)


static double ACOS (double x)
{
  // deal with numerical inaccuracy
  if (x<-1-TOL || x>1+TOL) {
    fprintf(stderr,"Unexpected value for acos: %.20g\n",x);
//    exit(1);
  }
  if (x<-1) x = -1;
  else if (x>1) x = 1;
  return (double)acos(x);
}

AlgQSpline::AlgQSpline ()
: m_n(-1), m_size(0), m_ind(0), m_Q(0), m_R(0), m_L(0), m_t(0), m_v(0),
  m_a(0), m_b(0), m_c(0), m_d0(0), m_d(0), m_auto_knot(2), m_def_v(0)
{
}

AlgQSpline::~AlgQSpline ()
{
  free(m_ind);
  free(m_Q);
  free(m_R);
  free(m_L);
  free(m_t);
  free(m_v);
}

AlgQSpline::Quat::Quat (double angle, double ux, double uy, double uz)
{
  double s = (double) sin(TORAD(angle)/2);
  double d = 1 / (double)sqrt(ux*ux + uy*uy + uz*uz);
  ux *= d; uy *= d; uz *= d;
  x = ux*s;
  y = uy*s;
  z = uz*s;
  w = (double)cos(TORAD(angle)/2);
}

void AlgQSpline::SetDefaultTension (double v)
{
  m_def_v = v;
}

void AlgQSpline::SetAutoKnotMethod (int autoknot)
{
  m_auto_knot = autoknot;
}

void AlgQSpline::Begin ()
{
  m_n = -1;
}

void AlgQSpline::AddOrientation (double angle, double ux, double uy, double uz)
{
  ++m_n; Reserve();
  m_Q[m_n] = CorrectDirection(Quat(angle,ux,uy,uz));
  m_v[m_n] = m_def_v;
  m_t[m_n] = (double)m_n;         // default: set inital value as uniform
}

void AlgQSpline::AddMatrix (double R[3][3])
{
  m_Q[m_n] = CorrectDirection(MatrixToQuat(R));
  m_v[m_n] = m_def_v;
  m_t[m_n] = (double)m_n;         // default: set inital value as uniform
}

void AlgQSpline::SetTension (double v)
{
  m_v[m_n] = v;
}

void AlgQSpline::SetKnot (double t)
{
  m_t[m_n] = t;
}

bool AlgQSpline::End ()
{
  AdjustSize();
  return Recompute();
}

bool AlgQSpline::ModifyOrientation (int i, double angle, double ux, double uy, double uz)
{
  if (i>=0 && i<=m_n) {
    m_Q[i] = CorrectDirection(Quat(angle,ux,uy,uz));
    return true;
  }
  else
    return false;
}

bool AlgQSpline::ModifyMatrix (int i, double R[3][3])
{
  if (i>=0 && i<=m_n) {
    m_Q[i] = CorrectDirection(MatrixToQuat(R));
    return true;
  }
  else
    return false;
}

bool AlgQSpline::ModifyKnot (int i, double t)
{
  if (i>=0 && i<=m_n) {
    m_t[i] = t;
    return true;
  }
  else
    return false;
}

bool AlgQSpline::ModifyTension (int i, double v)
{
  if (i>=0 && i<=m_n) {
    m_v[i] = v;
    return true;
  }
  else
    return false;
}

bool AlgQSpline::Recompute ()
{
  if (m_n < 1)
    return false;
  GenerateKnot();
  EliminateDuplications();
  AllocTemp();
  FillA();
  FillB();
  FillC();
  bool status = Solve4DSpline();
  if (status) {
    Normalize(m_d0);
    SolveQSpline();
    FillRL();
  }
  FreeTemp();
  return status;
}

void AlgQSpline::GetOrientation (double t, double* angle, double* ux, double* uy, double* uz)
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
    QuatToOrientation(m_Q[i0],angle,ux,uy,uz);
    return;
  }

  // compute interpolated position
  Quat b0 = Geodesic(t,m_Q[i0],m_R[i0]);
  Quat b1 = Geodesic(t,m_R[i0],m_L[i0]);
  Quat b2 = Geodesic(t,m_L[i0],m_Q[i1]);
  b0 = Geodesic(t,b0,b1);
  b1 = Geodesic(t,b1,b2);
  b0 = Geodesic(t,b0,b1);
  
  QuatToOrientation(b0,angle,ux,uy,uz);
}

int AlgQSpline::GetNOrientations ()
{
  return m_n+1;
}

void AlgQSpline::GetGivenOrientation (int i, double* angle, double* ux, double* uy, double* uz)
{
  assert(i>=0 && i<m_size);
  QuatToOrientation(m_Q[m_ind[i]],angle,ux,uy,uz);
}

void AlgQSpline::QuatToOrientation (const AlgQSpline::Quat& q, double* angle, double* ux, double* uy, double* uz)
{
  double a = (double)ACOS(q.w);
  double s = (double)sin(a);
  *angle = TODEG(2*a);
  if (fabs(s)>NTOL) {
   *ux = q.x/s;
   *uy = q.y/s;
   *uz = q.z/s;
  }
  else {
    *ux = 1;
    *uy = *uz = 0;
  }
}

double AlgQSpline::GetKnot (int i)
{
  assert(i>=0 && i<m_size);
  return m_t[m_ind[i]];
}

double AlgQSpline::GetTension (int i)
{
  assert(i>=0 && i<m_size);
  return m_v[m_ind[i]];
}

// PRIVATE METHODS

const AlgQSpline::Quat& AlgQSpline::MatrixToQuat (double R[3][3])
{
  static Quat q;
  q.x = sqrt(1+R[0][0]-R[1][1]-R[2][2])/4.0;
  q.y = sqrt(1-R[0][0]+R[1][1]-R[2][2])/4.0;
  q.z = sqrt(1-R[0][0]-R[1][1]+R[2][2])/4.0;
  q.w = sqrt(1+R[0][0]+R[1][1]+R[2][2])/4.0;
  if (q.x > q.y && q.x > q.z && q.x > q.w) {
    q.y = (R[0][1] + R[1][0])/4/q.x;
    q.z = (R[2][0] + R[0][2])/4/q.x;
    q.w = (R[1][2] - R[2][1])/4/q.x;
  }
  else if (q.y > q.x && q.y > q.z && q.y > q.w) {
    q.x = (R[0][1] + R[1][0])/4/q.y;
    q.z = (R[1][2] + R[2][1])/4/q.y;
    q.w = (R[2][0] - R[0][2])/4/q.y;
  }
  else if (q.z > q.x && q.z > q.y && q.z > q.w) {
    q.x = (R[2][0] + R[0][2])/4/q.z;
    q.y = (R[1][2] + R[2][1])/4/q.z;
    q.w = (R[0][1] - R[1][0])/4/q.z;
  }
  else {
    q.x = (R[1][2] - R[2][1])/4/q.w;
    q.y = (R[2][0] - R[0][2])/4/q.w;
    q.z = (R[0][1] - R[1][0])/4/q.w;
  }
  return q;
}

const AlgQSpline::Quat& AlgQSpline::CorrectDirection (const AlgQSpline::Quat& q)
{
  if (m_n != 0) {
    static Quat qneg;
    qneg.x = -q.x; qneg.y = -q.y; qneg.z = -q.z; qneg.w = -q.w;
    double a = Angle(q,m_Q[m_n-1]);
    double aneg = Angle(qneg,m_Q[m_n-1]);
    if (fabs(aneg) < fabs(a))
      return qneg;
  }
  return q;
}

void AlgQSpline::FillA ()
{
  m_a[0] = 0; // undefined, not used
  m_a[m_n] = 0;
  for (int i=1; i<m_n; ++i)
    m_a[i] = (1-Di(i)) * (1-Li(i));
}

void AlgQSpline::FillB ()
{
  m_b[0] = 1;
  m_b[m_n] = 1;
  for (int i=1; i<m_n; ++i)
    m_b[i] = (1-Di(i))*Li(i) + Di(i)*(1-Mi(i));
}

void AlgQSpline::FillC ()
{
  m_c[0] = 0;
  m_c[m_n] = 0; // undefined, not used
  for (int i=1; i<m_n; ++i)
    m_c[i] = Di(i)*Mi(i);
}

// Solve tridiagonal system for 4D-Spline
// Ref. Numerical Recipes
bool AlgQSpline::Solve4DSpline ()
{
  int i;
  int n = m_n+1;
  double bet;
  double* a = m_a;
  double* b = m_b;
  double* c = m_c;
  Quat* r = m_Q;
  Quat* u = m_d0;

  if (fabs(b[0]) < NTOL)
    return false;

  double* gam = (double*) malloc(n*sizeof(double));  // temp workspace
  bet = b[0];
  u[0].x = r[0].x/bet;
  u[0].y = r[0].y/bet;
  u[0].z = r[0].z/bet;
  u[0].w = r[0].w/bet;
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
    u[i].w = (r[i].w - a[i]*u[i-1].w) / bet;
  }
  for (i=n-2; i>=0; --i) {
    u[i].x -= gam[i+1] * u[i+1].x;
    u[i].y -= gam[i+1] * u[i+1].y;
    u[i].z -= gam[i+1] * u[i+1].z;
    u[i].w -= gam[i+1] * u[i+1].w;
  }
  free(gam);
  return true;
}

void AlgQSpline::Normalize (AlgQSpline::Quat* d)
{
  for (int i=0; i<=m_n; ++i) {
    double v = 1/(double)sqrt(d[i].x*d[i].x + d[i].y*d[i].y + 
                               d[i].z*d[i].z + d[i].w*d[i].w
                              );
    d[i].x *= v;
    d[i].y *= v;
    d[i].z *= v;
    d[i].w *= v;
  }
}

void AlgQSpline::GenerateKnot ()
{
  if (m_auto_knot != 0) {
    m_t[0] = 0;
    for (int i=1; i<=m_n; ++i) {
      m_t[i] = m_t[i-1] + (m_auto_knot==1 ? 1 : Angle(m_Q[i],m_Q[i-1]));
    }
  }
}

void AlgQSpline::EliminateDuplications ()
{
  int i = 0;
  int k = 0;
  m_ind[i++] = k++;
  while (i <= m_n) {
    if (Angle(m_Q[i],m_Q[i-1]) < TOL) {
      memmove(&m_Q[i],&m_Q[i+1],(m_n-i)*sizeof(Quat));
      memmove(&m_t[i],&m_t[i+1],(m_n-i)*sizeof(double));
      memmove(&m_v[i],&m_v[i+1],(m_n-i)*sizeof(double));
      m_n--;
      m_ind[k++] = i-1;
    }
    else {
      m_ind[k++] = i++;
    }
  }
}

double AlgQSpline::Angle (const AlgQSpline::Quat& q0, const AlgQSpline::Quat& q1) 
{
	double x = q0.x*q1.x + q0.y*q1.y + q0.z*q1.z + q0.w*q1.w;
  return (double)ACOS(x);
}

const AlgQSpline::Quat& AlgQSpline::Geodesic (double t, const AlgQSpline::Quat& q0, const AlgQSpline::Quat& q1)
{
  static Quat q;
  double teta = Angle(q0,q1); 
  double v = (double)sin(teta);
  if (fabs(v) < NTOL)
    return q0;
  double v0 = (double)sin((1-t)*teta);
  double v1 = (double)sin(t*teta);
  q.x = v0/v*q0.x + v1/v*q1.x;
  q.y = v0/v*q0.y + v1/v*q1.y;
  q.z = v0/v*q0.z + v1/v*q1.z;
  q.w = v0/v*q0.w + v1/v*q1.w;
  return q;
}

void AlgQSpline::SolveQSpline ()
{
  int k = 0;
  double error;
  Quat* d = m_d0;
  Quat* d0 = m_d;
  do {
    Quat* temp = d; d = d0; d0 = temp;
    d[0] = m_Q[0];
    d[m_n] = m_Q[m_n];
    for (int i=1; i<m_n; ++i) {
      double alpha0 = Angle(d0[i-1],d0[i]);
      double alpha1 = Angle(d0[i],d0[i+1]);
      Quat L = Geodesic(Li(i),d0[i-1],d0[i]);
      Quat R = Geodesic(Mi(i),d0[i],d0[i+1]);
      double beta = Angle(L,R);
      double a = (double)sin(beta);
      double b = (double)((sin((1-Di(i))*beta) * sin((1-Li(i))*alpha0)) / sin(alpha0));
      double c = (double)((sin(Di(i)*beta) * sin(Mi(i)*alpha1)) / sin(alpha1));

      if (fabs(beta)<NTOL || fabs(alpha0)<NTOL || fabs(alpha1)<NTOL)
        d[i] = d[i-1];
      else {
        double w = (double)((sin((1-Di(i))*beta) * sin(Li(i)*alpha0)) / sin(alpha0) +
                          (sin(Di(i)*beta) * sin((1-Mi(i))*alpha1)) / sin(alpha1)
                          );
        assert(w);
        d[i].x = (a*m_Q[i].x - b*d0[i-1].x - c*d0[i+1].x) / w;
        d[i].y = (a*m_Q[i].y - b*d0[i-1].y - c*d0[i+1].y) / w;
        d[i].z = (a*m_Q[i].z - b*d0[i-1].z - c*d0[i+1].z) / w;
        d[i].w = (a*m_Q[i].w - b*d0[i-1].w - c*d0[i+1].w) / w;
      }
    }
    Normalize(d);
    k++;
    error = EvalMaxError(d,d0);
  } while (error > TOL && k < KMAX);
  // final value must be stored at m_d
  if (d != m_d)
    memcpy(m_d,d,(m_n+1)*sizeof(Quat));
}

double AlgQSpline::EvalMaxError (Quat* d, Quat* d0)
{
  double ex, ey, ez, ew;
  double nx=0, ny=0, nz=0, nw=0;
  double dx=0, dy=0, dz=0, dw=0;
  for (int i=0; i<=m_n; ++i) {
    nx += (d[i].x - d0[i].x) * (d[i].x - d0[i].x);
    ny += (d[i].y - d0[i].y) * (d[i].y - d0[i].y);
    nz += (d[i].z - d0[i].z) * (d[i].z - d0[i].z);
    nw += (d[i].w - d0[i].w) * (d[i].w - d0[i].w);
    dx += d[i].x * d[i].x;
    dy += d[i].y * d[i].y;
    dz += d[i].z * d[i].z;
    dw += d[i].w * d[i].w;
  }
  ex = (double)sqrt(nx/dx);
  ey = (double)sqrt(ny/dy);
  ez = (double)sqrt(nz/dz);
  ew = (double)sqrt(nw/dw);
  double emax = ex;
  if (ey > emax) emax = ey;
  if (ez > emax) emax = ez;
  if (ew > emax) emax = ew;
  return emax;
}

void AlgQSpline::FillRL ()
{
  for (int i=0; i<m_n; ++i) {
    m_R[i] = Geodesic(Mi(i),m_d[i],m_d[i+1]);
    m_L[i] = Geodesic(Li(i+1),m_d[i],m_d[i+1]);
  }
}

void AlgQSpline::Reserve ()
{
  if (m_size <= m_n+1) {
    m_size = m_size==0 ? 4 : 2*m_size;
    m_ind = (int*) realloc(m_ind,m_size*sizeof(int));
    m_Q = (Quat*) realloc(m_Q,m_size*sizeof(Quat));
    m_R = (Quat*) realloc(m_R,(m_size-1)*sizeof(Quat));
    m_L = (Quat*) realloc(m_L,(m_size-1)*sizeof(Quat));
    m_t = (double*) realloc(m_t,m_size*sizeof(double));
    m_v = (double*) realloc(m_v,m_size*sizeof(double));
  }
}

void AlgQSpline::AdjustSize ()
{
  m_size = m_n+1;
  if (m_size)
  {
    m_ind = (int*) realloc(m_ind,m_size*sizeof(int));
    m_Q = (Quat*) realloc(m_Q,m_size*sizeof(Quat));
    m_R = (Quat*) realloc(m_R,(m_size-1)*sizeof(Quat));
    m_L = (Quat*) realloc(m_L,(m_size-1)*sizeof(Quat));
    m_t = (double*) realloc(m_t,m_size*sizeof(double));
    m_v = (double*) realloc(m_v,m_size*sizeof(double));
  }
}

void AlgQSpline::AllocTemp ()
{
  m_a = (double*) malloc(m_size*sizeof(double));
  m_b = (double*) malloc(m_size*sizeof(double));
  m_c = (double*) malloc(m_size*sizeof(double));
  m_d0 = (Quat*) malloc(m_size*sizeof(Quat));
  m_d  = (Quat*) malloc(m_size*sizeof(Quat));
}

void AlgQSpline::FreeTemp ()
{
  free(m_a);
  free(m_b);
  free(m_c);
  free(m_d0);
  free(m_d);
}

void AlgQSpline::Debug ()
{
  int i;
  printf("\n");
  for (i=0; i<m_n; ++i) {
    printf("Q[%d]: %.3f %.3f %.3f %.3f\n",i,m_Q[i].x,m_Q[i].y,m_Q[i].z,TODEG(2*ACOS(m_Q[i].w)));
    printf("R[%d]: %.3f %.3f %.3f %.3f\n",i,m_R[i].x,m_R[i].y,m_R[i].z,TODEG(2*ACOS(m_R[i].w)));
    printf("L[%d]: %.3f %.3f %.3f %.3f\n",i,m_L[i].x,m_L[i].y,m_L[i].z,TODEG(2*ACOS(m_L[i].w)));
  }
  printf("Q[%d]: %.3f %.3f %.3f %.3f\n",m_n,m_Q[m_n].x,m_Q[m_n].y,m_Q[m_n].z,TODEG(2*ACOS(m_Q[i].w)));

  for (i=0; i<=m_n; ++i)
    printf("t[%d]: %.2f\n",i,m_t[i]);
  for (i=0; i<=m_n; ++i)
    printf("v[%d]: %.2f\n",i,m_v[i]);
}


