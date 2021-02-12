//* matrix.h
// Implements a 4x4 matrix to support graphics operation.
// celes@tecgraf.puc-rio.br
// fabraham@tecgraf.puc-rio.br
// Jun 2002

#ifndef ALG_MATRIX_H
#define ALG_MATRIX_H

#include "defines.h"
#include "vector.h"
#include "quatern.h"
#include "plane.h"
#include <ds/stack.h>
#include <string.h>

class ALG_API AlgMatrix
{
  float m_v[16];
public:
  static AlgMatrix GetIdentity ();
  AlgMatrix()
  {
  }
  /**
   * Copy constructor
   */
  AlgMatrix (const AlgMatrix& m)
  {
    memcpy(m_v,m.m_v,16*sizeof(float));
  }
  AlgMatrix (const float *v)
  {
    memcpy(m_v,v,16*sizeof(float));
  }
  AlgMatrix (const double *v)
  {
    for(int i=0; i<16; i++)
      m_v[i] = (float)v[i];
  }
	AlgMatrix(const AlgVector& x, const AlgVector& y, const AlgVector& z);
  void operator = (const AlgMatrix&m);
	void operator = (const float* m);
  void Identity ();
  void Translate (float x, float y, float z);
  void Translate (const AlgVector& v);
  void Scale (float x, float y, float z);
  void Scale (const AlgVector& v);
  void Scale (float x, float y, float z, float rx, float ry, float rz);
  void Scale (const AlgVector& v, const AlgVector& r);
  void Scale (float s);
  void Rotate (float a, float x, float y, float z);
  void Rotate (float a, const AlgVector& p);
  void Rotate (const AlgQuatern& q);
  void Rotate (float a, float x, float y, float z, float rx, float ry, float rz);
  void Rotate (float a, const AlgVector& p, const AlgVector& r);
  void Rotate (const AlgQuatern& q, const AlgVector& r);

  void LookAt      (const AlgVector& pos, const AlgVector& target, const AlgVector& up);
  void Ortho       (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar);
  void Frustum     (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar);
  void Perspective (float fovy, float aspect, float znear, float zfar);

  void Accum (const AlgMatrix& m);
  void PreAccum(const AlgMatrix& m);
  void SetMatrix (const float* v);
  void SetMatrix (const double* v);
  void Transpose ();
  bool IsIdentity () const;
  void Invert ();
  AlgMatrix Inverse () const;
  AlgVector Transform(float x, float y, float z) const;
  void      Transform(float*x, float*y, float*z) const;
  void      Transform(float*x, float*y, float*z, float*w) const;
  void      Transform(int n, int nelem, float *v) const;
  AlgVector Transform(const AlgVector& p) const;
  AlgVector TransformNormal(float nx, float ny, float nz) const;
  AlgVector TransformNormal(const AlgVector& n) const;
  void      TransformNormals(int n, float *v) const;
  AlgPlane  TransformPlane(float a, float b, float c, float d) const;
  AlgPlane  TransformPlane(const AlgPlane& p) const;
  AlgVector TransformVector(float vx, float vy, float vz) const;
  AlgVector TransformVector(const AlgVector& v) const;

  const float* GetMatrix () const
  {
    return m_v;
  }
  void GetMatrixDouble (double* v) const
  {
    int i;
    for (i=0; i<16; i++)
      v[i] = m_v[i];
  }
  void Print (const char* label=0) const;
  bool operator == (const AlgMatrix& m);
};

class ALG_API AlgStackMatrix : public DsStack<AlgMatrix>
{
public:
  AlgStackMatrix ()
    : DsStack<AlgMatrix>()
  {
    Init();
  }
	void Clear ()
  {
    DsStack<AlgMatrix>::Clear();
    Init();
  }
private:
  void Init ()
  {
    AlgMatrix m;
    m.Identity();
    Push(m);
  }
};

#endif
