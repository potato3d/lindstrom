//* matrix.cpp
// celes@tecgraf.puc-rio.br
// Jun 2002

#include <stdio.h>
#include <math.h>
#include "matrix.h"
#include "defines.h"

AlgMatrix* s_identity = NULL;

AlgMatrix AlgMatrix::GetIdentity ()
{
  if (s_identity == NULL)
  {
    s_identity = new AlgMatrix();
    s_identity->Identity();
  }
  return *s_identity;
}

AlgMatrix::AlgMatrix(const AlgVector& x, const AlgVector& y, const AlgVector& z)
{
  m_v[0] = x.x; m_v[4] = x.y; m_v[8] = x.z;  m_v[12] = 0.0f;
  m_v[1] = y.x; m_v[5] = y.y; m_v[9] = y.z; m_v[13] = 0.0f;
  m_v[2] = z.x; m_v[6] = z.y; m_v[10] = z.z; m_v[14] = 0.0f;
  m_v[3] = 0.0f;  m_v[7] = 0.0f;  m_v[11] = 0.0f;  m_v[15] = 1.0f;
}

void AlgMatrix::Identity ()
{
  m_v[1]  = m_v[2]  = m_v[3]  = m_v[4] = 
  m_v[6]  = m_v[7]  = m_v[8]  = m_v[9] = 
  m_v[11] = m_v[12] = m_v[13] = m_v[14] = 0.0F;
  m_v[0]  = m_v[5]  = m_v[10] = m_v[15] = 1.0F;
}

void AlgMatrix::Translate (float x, float y, float z)
{
  AlgMatrix m;
  m.Identity();
  m.m_v[12] = x;
  m.m_v[13] = y;
  m.m_v[14] = z;
  Accum(m);
}

void AlgMatrix::Translate (const AlgVector& v)
{
  Translate(v.x,v.y,v.z);
}

void AlgMatrix::Scale (float x, float y, float z)
{
  AlgMatrix m;
  m.Identity();
  m.m_v[0] = x;
  m.m_v[5] = y;
  m.m_v[10] = z;
  Accum(m);
}

void AlgMatrix::Scale (const AlgVector& v)
{
  Scale(v.x,v.y,v.z);
}

void AlgMatrix::Scale (float x, float y, float z, float rx, float ry, float rz)
{
  Translate(rx,ry,rz);
  Scale(x,y,z);
  Translate(-rx,-ry,-rz);
}

void AlgMatrix::Scale (const AlgVector& v, const AlgVector& r)
{
  Translate(r.x,r.y,r.z);
  Scale(v.x,v.y,v.z);
  Translate(-r.x,-r.y,-r.z);
}

void AlgMatrix::Scale (float s)
{
  Scale(s,s,s);
}

void AlgMatrix::Rotate (float a, float x, float y, float z)
{
  AlgVector p(x,y,z);
  Rotate(a,p);
}

void AlgMatrix::Rotate (float a, const AlgVector& p) 
{
  float r = a*ALG_PI/180.0F;
  float c = (float)cos(r);
  float s = (float)sin(r);
  AlgMatrix m;
  AlgVector n(p);
  n.Normalize();
  m.m_v[0] = c+(1.0F-c)*n.x*n.x;
  m.m_v[1] = (1.0F-c)*n.x*n.y+n.z*s;
  m.m_v[2] = (1.0F-c)*n.x*n.z-n.y*s;
  m.m_v[3] = 0.0F; 
  m.m_v[4] = (1.0F-c)*n.x*n.y-n.z*s; 
  m.m_v[5] = c+(1.0F-c)*n.y*n.y; 
  m.m_v[6] = (1.0F-c)*n.y*n.z+n.x*s; 
  m.m_v[7] = 0.0F;
  m.m_v[8] = (1.0F-c)*n.x*n.z+n.y*s;
  m.m_v[9] = (1.0F-c)*n.y*n.z-n.x*s; 
  m.m_v[10] = c+(1.0F-c)*n.z*n.z; 
  m.m_v[11] = 0.0F; 
  m.m_v[12] = 0.0F; 
  m.m_v[13] = 0.0F; 
  m.m_v[14] = 0.0F;
  m.m_v[15] = 1.0F; 
  Accum(m);
}

void AlgMatrix::Rotate (const AlgQuatern& q)
{
  float x,y,z;
  q.GetAxis(&x,&y,&z);
  Rotate(q.GetAngle(),x,y,z);
}

void AlgMatrix::Rotate (const AlgQuatern& q, const AlgVector& r)
{
  float x,y,z;
  q.GetAxis(&x,&y,&z);
  Translate(r.x,r.y,r.z);
  Rotate(q.GetAngle(),x,y,z);
  Translate(-r.x,-r.y,-r.z);
}

void AlgMatrix::Rotate (float a, const AlgVector& p, const AlgVector& r)
{
  Translate(r.x,r.y,r.z);
  Rotate(a,p);
  Translate(-r.x,-r.y,-r.z);
}

void AlgMatrix::Rotate (float a, float x, float y, float z, float rx, float ry, float rz)
{
  Translate(rx,ry,rz);
  Rotate(a,x,y,z);
  Translate(-rx,-ry,-rz);
}

void AlgMatrix::LookAt (const AlgVector& pos, const AlgVector& target, const AlgVector& up)
{
  AlgVector vf  = target-pos;
  vf.Normalize();
  AlgVector vup = up;
  AlgVector vs;
  vs.Cross(vf,vup);
  vs.Normalize();
  vup.Cross(vs,vf);
  vup.Normalize();

	AlgMatrix m;
  m.m_v[0] = vs.x;  m.m_v[4] = vs.y;  m.m_v[8]  = vs.z;  m.m_v[12] = 0.0f;
  m.m_v[1] = vup.x; m.m_v[5] = vup.y; m.m_v[9]  = vup.z; m.m_v[13] = 0.0f;
  m.m_v[2] = -vf.x; m.m_v[6] = -vf.y; m.m_v[10] = -vf.z; m.m_v[14] = 0.0f;
  m.m_v[3] = 0.0f;  m.m_v[7] = 0.0f;  m.m_v[11] = 0.0f;  m.m_v[15] = 1.0f;

  Accum(m);
  Translate(-pos.x,-pos.y,-pos.z);
}

void AlgMatrix::Ortho (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar)
{
	AlgMatrix m;	
  m.m_v[0]  = 2.0f/(pright-pleft);
  m.m_v[4]  = 0.0f;
  m.m_v[8]  = 0.0f;
  m.m_v[12] = -(pright+pleft)/(pright-pleft);

	m.m_v[1]  = 0.0f;
	m.m_v[5]  = 2.0f/(ptop-pbottom);
	m.m_v[9]  = 0.0f;
	m.m_v[13] = -(ptop+pbottom)/(ptop-pbottom);

	m.m_v[2]  = 0.0f;
	m.m_v[6]  = 0.0f;
	m.m_v[10] = 2.0f/(pnear-pfar);
	m.m_v[14] = -(pfar+pnear)/(pfar-pnear);

	m.m_v[3]  = 0.0f;
	m.m_v[7]  = 0.0f;
	m.m_v[11] = 0.0f;
	m.m_v[15] = 1.0f;

	Accum(m);
}

void AlgMatrix::Frustum (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar)
{
	AlgMatrix m;
  m.m_v[0]  = 2.0f*pnear/(pright-pleft);
  m.m_v[4]  = 0.0f;
  m.m_v[8]  = (pright+pleft)/(pright-pleft);
  m.m_v[12] = 0.0f;

	m.m_v[1]  = 0.0f;
	m.m_v[5]  = 2.0f*pnear/(ptop-pbottom);
	m.m_v[9]  = (ptop+pbottom)/(ptop-pbottom);
	m.m_v[13] = 0.0f;

	m.m_v[2]  = 0.0f;
	m.m_v[6]  = 0.0f;
	m.m_v[10] = (pnear+pfar)/(pnear-pfar);
	m.m_v[14] = 2.0f*pnear*pfar/(pnear-pfar);

	m.m_v[3]  = 0.0f;
	m.m_v[7]  = 0.0f;
	m.m_v[11] = -1.0f;
	m.m_v[15] = 0.0f;
	Accum(m);
}

void AlgMatrix::Perspective (float fovy, float aspect, float znear, float zfar)
{
  float tan_fovy = (float)tan(ALG_PI*fovy*0.5/180.0);
  float right    = tan_fovy * aspect * znear;
  float left     = -right;
  float top      = tan_fovy * znear;
  float bottom   = -top;
  Frustum(left,right,bottom,top,znear,zfar);
}

void AlgMatrix::Accum (const AlgMatrix& m)
{
  int i,j,k,l;
  AlgMatrix n(*this);
  for (i=0; i<4; ++i)
  {
    for (j=0; j<16; j+=4)
    {
      m_v[j+i] = 0.0F;
      for (k=0,l=0; k<4; ++k,l+=4)
        m_v[j+i] += n.m_v[l+i] * m.m_v[j+k];
    }
  }
}

void AlgMatrix::PreAccum (const AlgMatrix& m)
{
  int i,j,k,l;
  AlgMatrix n(*this);
  for (i=0; i<4; ++i)
  {
    for (j=0; j<16; j+=4)
    {
      m_v[j+i] = 0.0F;
      for (k=0,l=0; k<4; ++k,l+=4)
        m_v[j+i] += m.m_v[l+i] * n.m_v[j+k];
    }
  }
}

void AlgMatrix::SetMatrix (const float* v)
{
  for (int i=0; i<16; ++i)
    m_v[i] = v[i];
}

void AlgMatrix::SetMatrix (const double* v)
{
  for (int i=0; i<16; ++i)
    m_v[i] = (float)v[i];
}

void AlgMatrix::Invert ()
{
 float m11 = m_v[0];
 float m21 = m_v[1];
 float m31 = m_v[2];
 float m41 = m_v[3];
 float m12 = m_v[4];
 float m22 = m_v[5];
 float m32 = m_v[6];
 float m42 = m_v[7];
 float m13 = m_v[8];
 float m23 = m_v[9];
 float m33 = m_v[10];
 float m43 = m_v[11];
 float m14 = m_v[12];
 float m24 = m_v[13];
 float m34 = m_v[14];
 float m44 = m_v[15];

 m_v[0] = (-m22*m33*m44+m22*m34*m43+m32*m23*m44-m32*m24*m43-m42*m23*m34+m42*m24*m33)/
          (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43- 
          m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44+
          m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
          m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23*
          m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[4] = (m12*m33*m44-m12*m34*m43-m32*m13*m44+m32*m14*m43+m42*m13*m34-m42*m14*m33)/
          (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
          m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44+
          m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
          m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23*
          m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[8] = (-m12*m23*m44+m12*m24*m43+m22*m13*m44-m22*m14*m43-m42*m13*m24+m42*m14*m23)/
          (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
          m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44+
          m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
          m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23*
          m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[12] = -(-m12*m23*m34+m12*m24*m33+m22*m13*m34-m22*m14*m33-m32*m13*m24+m32*m14*m23)/
           (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
           m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
           +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
           m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
           *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);
 
 m_v[1] = -(-m21*m33*m44+m21*m34*m43+m31*m23*m44-m31*m24*m43-m41*m23*m34+m41*m24*m33)/
          (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
          m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
          +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
          m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
          *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[5] = -(m11*m33*m44-m11*m34*m43-m31*m13*m44+m31*m14*m43+m41*m13*m34-m41*m14*m33)/
          (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
          m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
          +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
          m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
          *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[9] = -(-m11*m23*m44+m11*m24*m43+m21*m13*m44-m21*m14*m43-m41*m13*m24+m41*m14*m23)/
          (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
          m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
          +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
          m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
          *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[13] = (-m11*m23*m34+m11*m24*m33+m21*m13*m34-m21*m14*m33-m31*m13*m24+m31*m14*m23)/
           (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
           m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
           +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
           m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
           *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[2] = -(m21*m32*m44-m21*m34*m42-m31*m22*m44+m31*m24*m42+m41*m22*m34-m41*m24*m32)/
          (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
          m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
          +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
          m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
          *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[6] = (m11*m32*m44-m11*m34*m42-m31*m12*m44+m31*m14*m42+m41*m12*m34-m41*m14*m32)/
          (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
          m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
          +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
          m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
          *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[10] = -(m11*m22*m44-m11*m24*m42-m21*m12*m44+m21*m14*m42+m41*m12*m24-m41*m14*m22)/
           (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
           m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
           +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
           m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
           *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[14] = (m11*m22*m34-m11*m24*m32-m21*m12*m34+m21*m14*m32+m31*m12*m24-m31*m14*m22)/
           (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
           m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
           +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
           m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
           *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[3] = (m21*m32*m43-m21*m33*m42-m31*m22*m43+m31*m23*m42+m41*m22*m33-m41*m23*m32)/
          (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
          m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
          +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
          m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
          *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[7] = -(m11*m32*m43-m11*m33*m42-m31*m12*m43+m31*m13*m42+m41*m12*m33-m41*m13*m32)/
          (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
          m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
          +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
          m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
          *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[11] = (m11*m22*m43-m11*m23*m42-m21*m12*m43+m21*m13*m42+m41*m12*m23-m41*m13*m22)/
           (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
           m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
           +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
           m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
           *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

 m_v[15] = -(m11*m22*m33-m11*m23*m32-m21*m12*m33+m21*m13*m32+m31*m12*m23-m31*m13*m22)/
           (-m11*m22*m33*m44+m11*m22*m34*m43+m11*m32*m23*m44-m11*m32*m24*m43-
           m11*m42*m23*m34+m11*m42*m24*m33+m21*m12*m33*m44-m21*m12*m34*m43-m21*m32*m13*m44
           +m21*m32*m14*m43+m21*m42*m13*m34-m21*m42*m14*m33-m31*m12*m23*m44+m31*m12*m24*
           m43+m31*m22*m13*m44-m31*m22*m14*m43-m31*m42*m13*m24+m31*m42*m14*m23+m41*m12*m23
           *m34-m41*m12*m24*m33-m41*m22*m13*m34+m41*m22*m14*m33+m41*m32*m13*m24-m41*m32*m14*m23);

}

AlgMatrix AlgMatrix::Inverse () const
{
  AlgMatrix m = *this;
  m.Invert();
  return m;
}

AlgVector AlgMatrix::Transform (float x, float y, float z) const
{
  float w = m_v[3]*x + m_v[7]*y + m_v[11]*z + m_v[15];
  return AlgVector((m_v[0]*x + m_v[4]*y + m_v[8]*z + m_v[12])/w,
    (m_v[1]*x + m_v[5]*y + m_v[9]*z + m_v[13])/w,
    (m_v[2]*x + m_v[6]*y + m_v[10]*z + m_v[14])/w
    );
}

void AlgMatrix::Transform (float *x, float *y, float *z) const
{
  float oldx = *x, oldy = *y, oldz = *z;
  float w = m_v[3] * oldx + m_v[7] * oldy + m_v[11] * oldz + m_v[15];
  *x = (m_v[0]*oldx + m_v[4]*oldy + m_v[8] *oldz + m_v[12])/w;
  *y = (m_v[1]*oldx + m_v[5]*oldy + m_v[9] *oldz + m_v[13])/w;
  *z = (m_v[2]*oldx + m_v[6]*oldy + m_v[10]*oldz + m_v[14])/w;
}

void AlgMatrix::Transform (float *x, float *y, float *z, float *w) const
{
  float oldx = *x, oldy = *y, oldz = *z, oldw = *w;
  *x = m_v[0]*oldx + m_v[4]*oldy + m_v[8] *oldz + m_v[12]*oldw;
  *y = m_v[1]*oldx + m_v[5]*oldy + m_v[9] *oldz + m_v[13]*oldw;
  *z = m_v[2]*oldx + m_v[6]*oldy + m_v[10]*oldz + m_v[14]*oldw;
  *w = m_v[3]*oldx + m_v[7]*oldy + m_v[11]*oldz + m_v[15]*oldw;
}

void AlgMatrix::Transform (int n, int nelem, float *v) const
{
  int i;
  float x, y, z, w;
  switch(nelem)
  {
    case 2:
      for (i=0; i<n; i++, v+=2) // does this make sense? 
      {
        x = v[0];
        y = v[1];
        w = m_v[3]*x + m_v[7]*y + m_v[15];
        v[0] = (m_v[0]*x + m_v[4]*y + m_v[12])/w;
        v[1] = (m_v[1]*x + m_v[5]*y + m_v[13])/w;
      }
      return;
    case 3:
      for (i=0; i<n; i++, v+=3)
      {
        x = v[0];
        y = v[1];
        z = v[2];
        w    =  m_v[3]*x + m_v[7]*y + m_v[11]*z + m_v[15];
        v[0] = (m_v[0]*x + m_v[4]*y + m_v[8] *z + m_v[12])/w;
        v[1] = (m_v[1]*x + m_v[5]*y + m_v[9] *z + m_v[13])/w;
        v[2] = (m_v[2]*x + m_v[6]*y + m_v[10]*z + m_v[14])/w;
      }
      return;
    case 4:
      for (i=0; i<n; i++, v+=4)
      {
        x = v[0];
        y = v[1];
        z = v[2];
        w = v[3];
        v[0] = m_v[0]*x + m_v[4]*y + m_v[8] *z + m_v[12]*w;
        v[1] = m_v[1]*x + m_v[5]*y + m_v[9] *z + m_v[13]*w;
        v[2] = m_v[2]*x + m_v[6]*y + m_v[10]*z + m_v[14]*w;
        v[4] = m_v[3]*x + m_v[7]*y + m_v[11]*z + m_v[15]*w;
      }
      return;
  }
}

AlgVector AlgMatrix::Transform (const AlgVector& p) const
{
  return Transform(p.x,p.y,p.z);
}

AlgVector AlgMatrix::TransformNormal (const AlgVector& n) const
{
  return TransformNormal(n.x,n.y,n.z);
}

AlgVector AlgMatrix::TransformNormal(float x, float y, float z) const
{
  return AlgVector(m_v[0]*x + m_v[4]*y + m_v[8]*z,
                   m_v[1]*x + m_v[5]*y + m_v[9]*z,
                   m_v[2]*x + m_v[6]*y + m_v[10]*z
                  );
}

AlgPlane AlgMatrix::TransformPlane(float a, float b, float c, float d) const
{
   AlgPlane p;
   p.a = m_v[0]*a + m_v[1]*b + m_v[2]*c + m_v[3]*d;
   p.b = m_v[4]*a + m_v[5]*b + m_v[6]*c + m_v[7]*d;
   p.c = m_v[8]*a + m_v[9]*b + m_v[10]*c + m_v[11]*d;
   p.d = m_v[12]*a + m_v[13]*b + m_v[14]*c + m_v[15]*d;
   return p;
}


AlgPlane AlgMatrix::TransformPlane(const AlgPlane& p) const
{
  return TransformPlane(p.a,p.b,p.c,p.d);
}

AlgVector AlgMatrix::TransformVector(float vx, float vy, float vz) const
{
  // Vector v = (vx,vy,vz)-(0,0,0). Transform both points and return p2-p1.
  AlgVector p2 = Transform(vx,vy,vz);
  AlgVector p1(m_v[12]/m_v[15],m_v[13]/m_v[15],m_v[14]/m_v[15]);
  return p2-p1;
}

AlgVector AlgMatrix::TransformVector(const AlgVector& v) const
{
  return TransformVector(v.x,v.y,v.z);
}

void AlgMatrix::TransformNormals (int n, float *v) const
{
  int i;
  float x, y, z;
  for (i=0; i<n; i++, v+=3)
  {
    x = v[0];
    y = v[1];
    z = v[2];
    v[0] = m_v[0]*x + m_v[4]*y + m_v[8] *z;
    v[1] = m_v[1]*x + m_v[5]*y + m_v[9] *z;
    v[2] = m_v[2]*x + m_v[6]*y + m_v[10]*z;
  }
}

void AlgMatrix::Transpose()
{
  float temp;
  temp = m_v[1];  m_v[1]  = m_v[4];   m_v[4]  = temp;
  temp = m_v[2];  m_v[2]  = m_v[8];   m_v[8]  = temp;
  temp = m_v[3];  m_v[3]  = m_v[12];  m_v[12] = temp;
  temp = m_v[6];  m_v[6]  = m_v[9];   m_v[9]  = temp;
  temp = m_v[7];  m_v[7]  = m_v[13];  m_v[13] = temp;
  temp = m_v[11]; m_v[11] = m_v[14];  m_v[14] = temp;
}

void AlgMatrix::operator = (const float* m)
{
  m_v[0]=m[0];
  m_v[1]=m[1];
  m_v[2]=m[2];
  m_v[3]=m[3];
  m_v[4]=m[4];
  m_v[5]=m[5];
  m_v[6]=m[6];
  m_v[7]=m[7];
  m_v[8]=m[8];
  m_v[9]=m[9];
  m_v[10]=m[10];
  m_v[11]=m[11];
  m_v[12]=m[12];
  m_v[13]=m[13];
  m_v[14]=m[14];
  m_v[15]=m[15];
}

void AlgMatrix::operator = (const AlgMatrix&m)
{
	*this = m.m_v;
}

bool AlgMatrix::IsIdentity () const
{
  if ( m_v[0] == 1.0 && m_v[5] == 1.0 && m_v[10] == 1.0 && m_v[15] == 1.0 &&
       m_v[1] == 0.0 && m_v[4] == 0.0 && m_v[8 ] == 0.0 && m_v[12] == 0.0 &&
       m_v[2] == 0.0 && m_v[6] == 0.0 && m_v[9 ] == 0.0 && m_v[13] == 0.0 &&
       m_v[3] == 0.0 && m_v[7] == 0.0 && m_v[11] == 0.0 && m_v[14] == 0.0 ) 
  {
    return true;
  } 
  else
  {
    return false;
  }
}

void AlgMatrix::Print (const char* label) const
{
  int i,j;

  if (label)
    printf("%s\n",label);
  for (i=0; i<4; ++i)
  {
    for (j=0; j<16; j+=4)
      printf("%f ",m_v[j+i]);
    printf("\n");
  }
}

bool AlgMatrix::operator == (const AlgMatrix& m)
{
  return
    m_v[0] == m.m_v[0] && m_v[1] == m.m_v[1] && m_v[2] == m.m_v[2] &&
    m_v[3] == m.m_v[3] && m_v[4] == m.m_v[4] && m_v[5] == m.m_v[5] &&
    m_v[6] == m.m_v[6] && m_v[7] == m.m_v[7] && m_v[8] == m.m_v[8] &&
    m_v[9] == m.m_v[9] && m_v[10] == m.m_v[10] && m_v[11] == m.m_v[11] &&
    m_v[12] == m.m_v[12] && m_v[13] == m.m_v[13] && m_v[14] == m.m_v[14] &&
    m_v[15] == m.m_v[15];
}

