//* vector.h
// Represents 3D point.
// celes@tecgraf.puc-rio.br
// Jul 2002

#ifndef ALG_VECTOR_H
#define ALG_VECTOR_H

#include <math.h>
#include <stdio.h>

#include "defines.h"

class ALG_API AlgVector
{
public:
  float x, y, z;
  AlgVector ()
  {
  }
  AlgVector (float vx, float vy, float vz)
    : x(vx), y(vy), z(vz)
  {
  }
  AlgVector (const float v[3])
    : x(v[0]), y(v[1]), z(v[2])
  {
  }
  ~AlgVector ()
  {
  }
  void Set (float vx, float vy, float vz)
  {
    x = vx; y = vy; z = vz;
  }

  void Set (const float v[3])
  {
    x = v[0]; y = v[1]; z = v[2];
  }

  float Dot (const AlgVector& q) const
  {
    return x*q.x + y*q.y + z*q.z;
  }
  void Cross (const AlgVector& a, const AlgVector& b)
  {
    x = a.y*b.z - a.z*b.y;
    y = a.z*b.x - a.x*b.z;
    z = a.x*b.y - a.y*b.x;
  }

  float SqrLength() const
  {
    return (x*x+y*y+z*z);
  }

  float Length () const
  {
    return (float)sqrt(x*x+y*y+z*z);
  }
  /**
   * Normalizes the vector. Returns the previous vector norm.
   */
  float Normalize ()
  {
    float l = Length();
    if (l != 0.0f && ALG_FINITE(l))
    {
      float d = 1.0f/l;
      x *= d; y *= d; z *= d;
    }
    return l;
  }
  float Angle( const AlgVector& v ) const
  {
    return (float)(acos( Dot(v) / (Length()*v.Length()) ));
  }
  void Print (const char* label) const
  {
    printf("%s = {%g, %g, %g}\n",label,x,y,z);
  }
  //* Operators
  //* Add other vector in place
  AlgVector& operator+= (const AlgVector& other)
  {
    x += other.x; y += other.y; z += other.z;
    return *this;
  }
  //* Add a scalar in place
  AlgVector& operator+= (float scalar)
  {
    x += scalar; y += scalar; z += scalar;
    return *this;
  }
  //* Subtract other vector in place
  AlgVector& operator-= (const AlgVector& other)
  {
    x -= other.x; y -= other.y; z -= other.z;
    return *this;
  }
  //* Subtract a scalar in place
  AlgVector& operator-= (float scalar)
  {
    x -= scalar; y -= scalar; z -= scalar;
    return *this;
  }
  //* Unary minus operator
  AlgVector operator- ()
  {
    AlgVector v(-x,-y,-z);
    return v;
  }
  //* Multiply other vector, component by component, in place
  AlgVector& operator*= (const AlgVector& other)
  {
    x *= other.x; y *= other.y; z *= other.z;
    return *this;
  }
  //* Multiply a scalar in place
  AlgVector& operator*= (float scalar)
  {
    x *= scalar; y *= scalar; z *= scalar;
    return *this;
  }
  //* Divide by a scalar in place
  AlgVector& operator/= (float scalar)
  {
    x /= scalar; y /= scalar; z /= scalar;
    return *this;
  }
  //* Free operators
  friend bool operator == (const AlgVector& v1, const AlgVector& v2)
  {
    return (v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z);
  }
  friend bool operator != (const AlgVector& v1, const AlgVector& v2)
  {
    return (v1.x != v2.x) || (v1.y != v2.y) || (v1.z != v2.z);
  }

  //* Add two vectors
  friend AlgVector operator+ (const AlgVector& one, const AlgVector& other)
  {
    AlgVector res(one);
    return res+=other;
  }
  //* Add a vector and a scalar
  friend AlgVector operator+ (const AlgVector& one, float scalar)
  {
    AlgVector res(one);
    return res+=scalar;
  }
  //* Add a scalar and a vector
  friend AlgVector operator+ (float scalar, const AlgVector& one)
  {
    AlgVector res(one);
    return res+=scalar;
  }
  //* Subtract two vectors
  friend AlgVector operator- (const AlgVector& one, const AlgVector& other)
  {
    AlgVector res(one);
    return res-=other;
  }
  //* Subtract a vector by a scalar
  friend AlgVector operator- (const AlgVector& one, float scalar)
  {
    AlgVector res(one);
    return res-=scalar;
  }
  //* Subtract a scalar from a vector
  friend AlgVector operator- (float scalar, const AlgVector& one)
  {
    AlgVector res(one);
    res*=-1;
    return res+=scalar;
  }
  //* Multiply component by component
  friend AlgVector operator* (const AlgVector& one, const AlgVector& other)
  {
    AlgVector res(one.x*other.x,one.y*other.y,one.z*other.z);
    return res;
  }
  //* Multiply a vector by a scalar
  friend AlgVector operator* (const AlgVector& one, float scalar)
  {
    AlgVector res(one);
    return res*=scalar;
  }
  //* Multiply a scalar by a vector
  friend AlgVector operator* (float scalar, const AlgVector& one)
  {
    AlgVector res(one);
    return res*=scalar;
  }
  //* Divide a vector by a scalar
  friend AlgVector operator/ (const AlgVector& one, float scalar)
  {
    AlgVector res(one);
    return res/=scalar;
  }
  //* Divide a scalar by a vector
  friend AlgVector operator/ (float scalar, const AlgVector& one)
  {
    AlgVector res(scalar/one.x,scalar/one.y,scalar/one.z);
    return res;
  }
  //* Cross product
  friend AlgVector operator^ (const AlgVector& a, const AlgVector& b)
  {
    AlgVector res(a.y*b.z-b.y*a.z,b.x*a.z-a.x*b.z,a.x*b.y-b.x*a.y);
    return res;
  }
};

#endif

