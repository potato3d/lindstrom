#include "quatern.h"
#include <math.h>

static AlgQuatern s_SlerpNoInversion(const AlgQuatern& q0, const AlgQuatern& q1, float h)
{
   float dot = q0.Dot(q1);

   AlgQuatern ret;
   if (dot > -0.95f && dot < 0.95f)
   {
     float theta = (float)acos(dot);
     ret = AlgQuatern::Div(AlgQuatern::Add(AlgQuatern::Mult(q0, sin(theta*(1-h))), AlgQuatern::Mult(q1, sin(theta*h))), sin(theta));
   }
   else
     ret = AlgQuatern::Lerp(q0, q1, h);
   //ret.Normalize();
   return ret;
}

void AlgQuatern::Set(const AlgVector &u, const AlgVector &v, const AlgVector &w)
{
   float T = u.x + v.y + w.z + 1;
   if(T>=1)
   {
      m_w = (float)sqrt(T)*0.5f;
      float sqrtT2 = 2*(float)sqrt(T);
      m_p.x = (v.z - w.y) / sqrtT2;
      m_p.y = (w.x - u.z) / sqrtT2;
      m_p.z = (u.y - v.x) / sqrtT2;
   }
   else
   {
      if(u.x > v.y)
      {
         if(u.x > w.z)
         {
            // M11
            m_p.x = (float)sqrt(u.x - v.y - w.z + 1)*0.5f;
            m_p.y = (u.y + v.x) / (4*m_p.x);
            m_p.z = (u.z + w.x) / (4*m_p.x);
            m_w   = (v.z - w.y) / (4*m_p.x);
         }
         else
         {
            // M33
            m_p.z = (float)sqrt(w.z - u.x - v.y + 1)*0.5f;
            m_p.x = (w.x + u.z) / (4*m_p.z);
            m_p.y = (w.y + v.z) / (4*m_p.z);
            m_w   = (u.y - v.x) / (4*m_p.z);
         }
      }
      else if(v.y > w.z)
      {
         // M22
         m_p.y = (float)sqrt(v.y - u.x - w.z + 1)*0.5f;
         m_p.x = (v.x + u.y) / (4*m_p.y);
         m_p.z = (v.z + w.y) / (4*m_p.y);
         m_w   = (w.x - u.z) / (4*m_p.y);
      }
      else
      {
         // M33
         m_p.z = (float)sqrt(w.z - u.x - v.y + 1)*0.5f;
         m_p.x = (w.x + u.z) / (4*m_p.z);
         m_p.y = (w.y + v.z) / (4*m_p.z);
         m_w   = (u.y - v.x) / (4*m_p.z);
      }
   } 
   Normalize();
}


void AlgQuatern::Mult (const AlgQuatern& q)
{
   /*
   float qw = m_w;
   float rw = q.m_w;
   AlgVector qv = m_p;
   AlgVector rv = q.m_p;
   m_w = qw*rw - qv.Dot(rv);
   m_p.Cross(qv,rv);
   m_p.x += rw*qv.x + qw*rv.x;
   m_p.y += rw*qv.y + qw*rv.y;
   m_p.z += rw*qv.z + qw*rv.z;
   /*/
   AlgQuatern ret;
	ret.m_p.x = m_p.y*q.m_p.z - m_p.z*q.m_p.y + m_w*q.m_p.x + m_p.x*q.m_w;
	ret.m_p.y = m_p.z*q.m_p.x - m_p.x*q.m_p.z + m_w*q.m_p.y + m_p.y*q.m_w;
	ret.m_p.z = m_p.x*q.m_p.y - m_p.y*q.m_p.x + m_w*q.m_p.z + m_p.z*q.m_w;
	ret.m_w = m_w*q.m_w - m_p.x*q.m_p.x - m_p.y*q.m_p.y - m_p.z*q.m_p.z;
   SetRaw(ret.m_w, ret.m_p);
   //*/
}

bool AlgQuatern::Log()
{
   float t = acos(m_w);
   float sint = sin(t);
   m_w=0;
   if (sint > 0)
   {
     t = t/sin(t);
     m_p.x *= t;
     m_p.y *= t;
     m_p.z *= t;
   }
   else
   {
     m_p.x = m_p.y = m_p.z = 0;
   }
   return true;
}

bool AlgQuatern::Pow(float t)
{
   float theta = (float)acos(m_w);
   m_w = (float)cos(theta*t);
   float s = (float)sin(theta*t);
   m_p.x *= s;
   m_p.y *= s;
   m_p.z *= s;
   return true;
}

// Spherical Interpolation
AlgQuatern AlgQuatern::Slerp(const AlgQuatern& q0, const AlgQuatern& q1, float h)
{
   AlgQuatern qTemp;
   float dot = q0.Dot(q1);
   if (dot < 0)
   {
     dot = -dot;
     qTemp = AlgQuatern::Mult(q1, -1);
   }
   else
   {
     qTemp = q1;
   }

   AlgQuatern ret;
   if (dot < 0.95f )
   {
     float theta = (float)acos(dot);
     ret = AlgQuatern::Div(AlgQuatern::Add(AlgQuatern::Mult(q0, (float)sin(theta*(1-h))), AlgQuatern::Mult(qTemp, (float)sin(theta*h))), (float)sin(theta));
   }
   else
     ret = AlgQuatern::Lerp(q0, qTemp, h);
   //ret.Normalize();
   return ret;
}

// Cubic Interpolation
AlgQuatern AlgQuatern::Squad(const AlgQuatern& q0, const AlgQuatern& q1, const AlgQuatern& q2, const AlgQuatern& q3, float h)
{
   AlgQuatern qa, qb, s0, s1;
//   if(q0.IsEqual(q1))
//      s0 = q0;
//   else
   {
      qa = q1;
      qa.Inverse();
      qb = qa;

      qa.Mult(q2);
      qa.Normalize();
      qa.Log();

      qb.Mult(q0);
      qb.Normalize();
      qb.Log();

      qa.Add(qb);
//      if(qa.Norm()==0)
//         qa.SetRaw(1.0,0.0,0.0,0.0);
      qa.Div(-4);
      qa.Exp();

      s0 = q1;
      s0.Mult(qa);
   }

//   if(q2.IsEqual((AlgQuatern)q3))
//      s1 = q2;
//   else
   {
      qa = q2;
      qa.Inverse();
      qb = qa;

      qa.Mult(q3);
      qa.Normalize();
      qa.Log();

      qb.Mult(q1);
      qb.Normalize();
      qb.Log();

      qa.Add(qb);
//      if(qa.Norm()==0)
//         qa.SetRaw(1.0,0.0,0.0,0.0);
      qa.Div(-4);
      qa.Exp();

      s1 = q2;
      s1.Mult(qa);
   }

   qb = s_SlerpNoInversion(s_SlerpNoInversion(q1, q2, h), s_SlerpNoInversion(s0, s1, h), 2*h*(1-h));
//   qb = Slerp(Slerp(q1, q2, h), Slerp(s0, s1, h), 2*h*(1-h));

   return qb;
}
