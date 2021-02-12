// GL stack class
// fabraham@tecgraf.puc-rio.br
// Sep 2003

#ifndef ALG_GL_STACK_H
#define ALG_GL_STACK_H

#include "stack.h"
#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

/**
 * This class interfaces for the OpenGL matrix stack.
 * It defines methods for:
 * - setting the base matrix (eg. the projection+view matrix), so that identity() takes to this space.
 * - accumulating/pushing/popping transformations.
 * - obtaining the stack top
 */
class ALG_API AlgGLStack : public AlgStack
{
  AlgMatrix* m_identity;
public:
  AlgGLStack () : m_identity(0)
  {
  }
  virtual ~AlgGLStack ()
  {
    if (m_identity)
      delete m_identity;
  }
  void SetIdentity (AlgMatrix* m)
  {
    if (m)
    {
      if (m_identity)
        *m_identity = *m;
      else
        m_identity = new AlgMatrix((float*)m->GetMatrix());
    }
    else if (m_identity)
    {
      delete m_identity;
      m_identity = 0;
    }
  }
  void SetIdentity (AlgMatrix m)
  {
    SetIdentity(&m);
  }
  void SetIdentity (float* m)
  {
    if (m)
    {
      if (m_identity)
        *m_identity = m;
      else
        m_identity = new AlgMatrix(m);
    }
    else if (m_identity)
    {
      delete m_identity;
      m_identity = 0;
    }
  }
  AlgMatrix* GetIdentity() const
  {
    return m_identity;
  }
  virtual AlgMatrix GetTop ()
  {
    float modl[16];
    glGetFloatv(GL_MODELVIEW_MATRIX,modl);
    return AlgMatrix(modl);
  }
  virtual void Push ()
  {
    glPushMatrix();
  }
  virtual void Pop ()
  {
    glPopMatrix();
  }
  virtual void Identity ()
  {
    if (GetIdentity())
      glLoadMatrixf(GetIdentity()->GetMatrix());
    else
      glLoadIdentity();
  }
  virtual void LoadMatrix (const AlgMatrix& m)
  {
    if (GetIdentity())
    {
      glLoadMatrixf(GetIdentity()->GetMatrix());
      glMultMatrixf(m.GetMatrix());
    }
    else
      glLoadMatrixf(m.GetMatrix());
  }
  virtual void Translate (float x, float y, float z)
  {
    glTranslatef(x,y,z);
  }
  virtual void Translate (const AlgVector& v)
  {
    glTranslatef(v.x,v.y,v.z);
  }
  virtual void Scale (float x, float y, float z)
  {
    glScalef(x,y,z);
  }
  virtual void Scale (const AlgVector& v)
  {
    glScalef(v.x,v.y,v.z);
  }
  virtual void Scale (float x,float y,float z,float rx,float ry,float rz)
  {
    glTranslatef(rx,ry,rz);
    glScalef(x,y,z);
    glTranslatef(-rx,-ry,-rz);
  }
  virtual void Scale (const AlgVector& v, const AlgVector& r)
  {
    glTranslatef(r.x,r.y,r.z);
    glScalef(v.x,v.y,v.z);
    glTranslatef(-r.x,-r.y,-r.z);
  }
  virtual void Rotate (float a, float x, float y, float z)
  {
    glRotatef(a,x,y,z);
  }
  virtual void Rotate (float a, const AlgVector& p)
  {
    glRotatef(a,p.x,p.y,p.z);
  }
  virtual void Rotate (const AlgQuatern& q)
  {
    float x,y,z;
    q.GetAxis(&x,&y,&z);
    glRotatef(q.GetAngle(),x,y,z);
  }
  virtual void Rotate (float a,float x,float y,float z,float rx,float ry,float rz)
  {
    glTranslatef(rx,ry,rz);
    glRotatef(a,x,y,z);
    glTranslatef(-rx,-ry,-rz);
  }
  virtual void Rotate (float a, const AlgVector& p, const AlgVector& r)
  {
    glTranslatef(r.x,r.y,r.z);
    glRotatef(a,p.x,p.y,p.z);
    glTranslatef(-r.x,-r.y,-r.z);
  }
  virtual void Rotate (const AlgQuatern& q, const AlgVector& r)
  {
    float x,y,z;
    q.GetAxis(&x,&y,&z);
    glTranslatef(r.x,r.y,r.z);
    glRotatef(q.GetAngle(),x,y,z);
    glTranslatef(-r.x,-r.y,-r.z);
  }
  virtual void LookAt (const AlgVector& pos, const AlgVector& target, const AlgVector& up)
  {
    gluLookAt(pos.x,pos.y,pos.z,target.x,target.y,target.z,up.x,up.y,up.z);
  }
  virtual void Ortho (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar)
  {
    glOrtho(pleft,pright,pbottom,ptop,pnear,pfar);
  }
  virtual void Frustum (float pleft, float pright, float pbottom, float ptop, float pnear, float pfar)
  {
    glFrustum(pleft,pright,pbottom,ptop,pnear,pfar);
  }
  virtual void Perspective (float fovy, float aspect, float znear, float zfar)
  {
    gluPerspective(fovy,aspect,znear,zfar);
  }
  virtual void Accum (const AlgMatrix& m)
  {
    glMultMatrixf(m.GetMatrix());
  }
  virtual void PreAccum (const AlgMatrix& m) // TODO: untested
  {
    AlgMatrix top = GetTop();
    top.PreAccum(m);
    LoadMatrix(top);  
  }
};

#endif
