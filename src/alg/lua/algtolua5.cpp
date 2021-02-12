/*
** Lua binding: alg
** Generated automatically by tolua 5.0 on Thu Mar  1 17:15:17 2007.
*/

#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua.h"

/* Exported function */
#ifdef __cplusplus
 extern "C"
#endif
 TOLUA_API int tolua_alg_open (lua_State* tolua_S);

#include <alg/vector.h>
#include <alg/plane.h>
#include <alg/quatern.h>
#include <alg/matrix.h>
#include <alg/spline.h>
#ifndef __GNUG__
#pragma warning( disable : 4800 )
#endif

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_AlgVector (lua_State* tolua_S)
{
 AlgVector* self = (AlgVector*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_AlgPlane (lua_State* tolua_S)
{
 AlgPlane* self = (AlgPlane*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_AlgSpline (lua_State* tolua_S)
{
 AlgSpline* self = (AlgSpline*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_AlgQuatern (lua_State* tolua_S)
{
 AlgQuatern* self = (AlgQuatern*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}

static int tolua_collect_AlgMatrix (lua_State* tolua_S)
{
 AlgMatrix* self = (AlgMatrix*) tolua_tousertype(tolua_S,1,0);
 tolua_release(tolua_S,self);
 delete self;
 return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"AlgVector");
 tolua_usertype(tolua_S,"AlgPlane");
 tolua_usertype(tolua_S,"AlgSpline");
 tolua_usertype(tolua_S,"AlgQuatern");
 tolua_usertype(tolua_S,"AlgMatrix");
}

/* get function: x of class  AlgVector */
static int tolua_get_AlgVector_AlgVector_x(lua_State* tolua_S)
{
  AlgVector* self = (AlgVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->x);
 return 1;
}

/* set function: x of class  AlgVector */
static int tolua_set_AlgVector_AlgVector_x(lua_State* tolua_S)
{
  AlgVector* self = (AlgVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'x'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->x = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: y of class  AlgVector */
static int tolua_get_AlgVector_AlgVector_y(lua_State* tolua_S)
{
  AlgVector* self = (AlgVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->y);
 return 1;
}

/* set function: y of class  AlgVector */
static int tolua_set_AlgVector_AlgVector_y(lua_State* tolua_S)
{
  AlgVector* self = (AlgVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'y'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->y = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* get function: z of class  AlgVector */
static int tolua_get_AlgVector_AlgVector_z(lua_State* tolua_S)
{
  AlgVector* self = (AlgVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
#endif
 tolua_pushnumber(tolua_S,(lua_Number)self->z);
 return 1;
}

/* set function: z of class  AlgVector */
static int tolua_set_AlgVector_AlgVector_z(lua_State* tolua_S)
{
  AlgVector* self = (AlgVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable 'z'",NULL);
 if (!tolua_isnumber(tolua_S,2,0,&tolua_err))
 tolua_error(tolua_S,"#vinvalid type in variable assignment.",&tolua_err);
#endif
  self->z = ((float)  tolua_tonumber(tolua_S,2,0));
 return 0;
}

/* method: new of class  AlgVector */
static int tolua_alg_AlgVector_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  AlgVector* tolua_ret = (AlgVector*)  new AlgVector();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgVector");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  AlgVector */
static int tolua_alg_AlgVector_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgVector",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float vx = ((float)  tolua_tonumber(tolua_S,2,0));
  float vy = ((float)  tolua_tonumber(tolua_S,3,0));
  float vz = ((float)  tolua_tonumber(tolua_S,4,0));
 {
  AlgVector* tolua_ret = (AlgVector*)  new AlgVector(vx,vy,vz);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgVector");
 }
 }
 return 1;
tolua_lerror:
 return tolua_alg_AlgVector_new00(tolua_S);
}

/* method: delete of class  AlgVector */
static int tolua_alg_AlgVector_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgVector* self = (AlgVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
 tolua_release(tolua_S,self);
 delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}

/* method: Set of class  AlgVector */
static int tolua_alg_AlgVector_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgVector",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgVector* self = (AlgVector*)  tolua_tousertype(tolua_S,1,0);
  float vx = ((float)  tolua_tonumber(tolua_S,2,0));
  float vy = ((float)  tolua_tonumber(tolua_S,3,0));
  float vz = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'",NULL);
#endif
 {
  self->Set(vx,vy,vz);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}

/* method: Dot of class  AlgVector */
static int tolua_alg_AlgVector_Dot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgVector* self = (const AlgVector*)  tolua_tousertype(tolua_S,1,0);
  const AlgVector* q = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Dot'",NULL);
#endif
 {
  float tolua_ret = (float)  self->Dot(*q);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Dot'.",&tolua_err);
 return 0;
#endif
}

/* method: Cross of class  AlgVector */
static int tolua_alg_AlgVector_Cross00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgVector* self = (AlgVector*)  tolua_tousertype(tolua_S,1,0);
  const AlgVector* a = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
  const AlgVector* b = ((const AlgVector*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Cross'",NULL);
#endif
 {
  self->Cross(*a,*b);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Cross'.",&tolua_err);
 return 0;
#endif
}

/* method: Length of class  AlgVector */
static int tolua_alg_AlgVector_Length00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgVector* self = (const AlgVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Length'",NULL);
#endif
 {
  float tolua_ret = (float)  self->Length();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Length'.",&tolua_err);
 return 0;
#endif
}

/* method: Normalize of class  AlgVector */
static int tolua_alg_AlgVector_Normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgVector* self = (AlgVector*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Normalize'",NULL);
#endif
 {
  self->Normalize();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Normalize'.",&tolua_err);
 return 0;
#endif
}

/* method: Print of class  AlgVector */
static int tolua_alg_AlgVector_Print00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgVector",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgVector* self = (const AlgVector*)  tolua_tousertype(tolua_S,1,0);
  const char* label = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Print'",NULL);
#endif
 {
  self->Print(label);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Print'.",&tolua_err);
 return 0;
#endif
}

/* function: Intersect */
static int tolua_alg_Intersect00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgPlane",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgPlane",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const AlgPlane",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgPlane p1 = *((const AlgPlane*)  tolua_tousertype(tolua_S,1,0));
  const AlgPlane p2 = *((const AlgPlane*)  tolua_tousertype(tolua_S,2,0));
  const AlgPlane p3 = *((const AlgPlane*)  tolua_tousertype(tolua_S,3,0));
 {
  AlgVector tolua_ret =  Intersect(p1,p2,p3);
 {
#ifdef __cplusplus
 void* tolua_obj = new AlgVector(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_AlgVector),"AlgVector");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AlgVector));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"AlgVector");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Intersect'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  AlgPlane */
static int tolua_alg_AlgPlane_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgPlane",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  AlgPlane* tolua_ret = (AlgPlane*)  new AlgPlane();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgPlane");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  AlgPlane */
static int tolua_alg_AlgPlane_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgPlane",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float a = ((float)  tolua_tonumber(tolua_S,2,0));
  float b = ((float)  tolua_tonumber(tolua_S,3,0));
  float c = ((float)  tolua_tonumber(tolua_S,4,0));
  float d = ((float)  tolua_tonumber(tolua_S,5,0));
 {
  AlgPlane* tolua_ret = (AlgPlane*)  new AlgPlane(a,b,c,d);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgPlane");
 }
 }
 return 1;
tolua_lerror:
 return tolua_alg_AlgPlane_new00(tolua_S);
}

/* method: new of class  AlgPlane */
static int tolua_alg_AlgPlane_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgPlane",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const AlgVector* n = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
  float d = ((float)  tolua_tonumber(tolua_S,3,0));
 {
  AlgPlane* tolua_ret = (AlgPlane*)  new AlgPlane(*n,d);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgPlane");
 }
 }
 return 1;
tolua_lerror:
 return tolua_alg_AlgPlane_new01(tolua_S);
}

/* method: delete of class  AlgPlane */
static int tolua_alg_AlgPlane_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgPlane",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgPlane* self = (AlgPlane*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
 tolua_release(tolua_S,self);
 delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}

/* method: Set of class  AlgPlane */
static int tolua_alg_AlgPlane_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgPlane",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgPlane* self = (AlgPlane*)  tolua_tousertype(tolua_S,1,0);
  float a = ((float)  tolua_tonumber(tolua_S,2,0));
  float b = ((float)  tolua_tonumber(tolua_S,3,0));
  float c = ((float)  tolua_tonumber(tolua_S,4,0));
  float d = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'",NULL);
#endif
 {
  self->Set(a,b,c,d);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}

/* method: GetNormal of class  AlgPlane */
static int tolua_alg_AlgPlane_GetNormal00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgPlane",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgPlane* self = (AlgPlane*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNormal'",NULL);
#endif
 {
  AlgVector tolua_ret =  self->GetNormal();
 {
#ifdef __cplusplus
 void* tolua_obj = new AlgVector(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_AlgVector),"AlgVector");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AlgVector));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"AlgVector");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNormal'.",&tolua_err);
 return 0;
#endif
}

/* method: Normalize of class  AlgPlane */
static int tolua_alg_AlgPlane_Normalize00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgPlane",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgPlane* self = (AlgPlane*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Normalize'",NULL);
#endif
 {
  self->Normalize();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Normalize'.",&tolua_err);
 return 0;
#endif
}

/* method: Distance of class  AlgPlane */
static int tolua_alg_AlgPlane_Distance00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgPlane",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgPlane* self = (const AlgPlane*)  tolua_tousertype(tolua_S,1,0);
  const AlgVector* p = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Distance'",NULL);
#endif
 {
  float tolua_ret = (float)  self->Distance(*p);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Distance'.",&tolua_err);
 return 0;
#endif
}

/* method: Print of class  AlgPlane */
static int tolua_alg_AlgPlane_Print00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgPlane",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgPlane* self = (const AlgPlane*)  tolua_tousertype(tolua_S,1,0);
  const char* label = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Print'",NULL);
#endif
 {
  self->Print(label);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Print'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  AlgQuatern */
static int tolua_alg_AlgQuatern_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgQuatern",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  AlgQuatern* tolua_ret = (AlgQuatern*)  new AlgQuatern();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgQuatern");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  AlgQuatern */
static int tolua_alg_AlgQuatern_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgQuatern",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float angle = ((float)  tolua_tonumber(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
  float z = ((float)  tolua_tonumber(tolua_S,5,0));
 {
  AlgQuatern* tolua_ret = (AlgQuatern*)  new AlgQuatern(angle,x,y,z);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgQuatern");
 }
 }
 return 1;
tolua_lerror:
 return tolua_alg_AlgQuatern_new00(tolua_S);
}

/* method: new of class  AlgQuatern */
static int tolua_alg_AlgQuatern_new02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgQuatern",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float angle = ((float)  tolua_tonumber(tolua_S,2,0));
  const AlgVector* axis = ((const AlgVector*)  tolua_tousertype(tolua_S,3,0));
 {
  AlgQuatern* tolua_ret = (AlgQuatern*)  new AlgQuatern(angle,*axis);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgQuatern");
 }
 }
 return 1;
tolua_lerror:
 return tolua_alg_AlgQuatern_new01(tolua_S);
}

/* method: new of class  AlgQuatern */
static int tolua_alg_AlgQuatern_new03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgQuatern",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const AlgVector* u = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
  const AlgVector* v = ((const AlgVector*)  tolua_tousertype(tolua_S,3,0));
  const AlgVector* w = ((const AlgVector*)  tolua_tousertype(tolua_S,4,0));
 {
  AlgQuatern* tolua_ret = (AlgQuatern*)  new AlgQuatern(*u,*v,*w);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgQuatern");
 }
 }
 return 1;
tolua_lerror:
 return tolua_alg_AlgQuatern_new02(tolua_S);
}

/* method: delete of class  AlgQuatern */
static int tolua_alg_AlgQuatern_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgQuatern",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgQuatern* self = (AlgQuatern*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
 tolua_release(tolua_S,self);
 delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}

/* method: Set of class  AlgQuatern */
static int tolua_alg_AlgQuatern_Set00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgQuatern",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgQuatern* self = (AlgQuatern*)  tolua_tousertype(tolua_S,1,0);
  float angle = ((float)  tolua_tonumber(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
  float z = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'",NULL);
#endif
 {
  self->Set(angle,x,y,z);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Set'.",&tolua_err);
 return 0;
#endif
}

/* method: Set of class  AlgQuatern */
static int tolua_alg_AlgQuatern_Set01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgQuatern",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  AlgQuatern* self = (AlgQuatern*)  tolua_tousertype(tolua_S,1,0);
  float angle = ((float)  tolua_tonumber(tolua_S,2,0));
  const AlgVector* axis = ((const AlgVector*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'",NULL);
#endif
 {
  self->Set(angle,*axis);
 }
 }
 return 0;
tolua_lerror:
 return tolua_alg_AlgQuatern_Set00(tolua_S);
}

/* method: Set of class  AlgQuatern */
static int tolua_alg_AlgQuatern_Set02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgQuatern",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  AlgQuatern* self = (AlgQuatern*)  tolua_tousertype(tolua_S,1,0);
  const AlgVector* u = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
  const AlgVector* v = ((const AlgVector*)  tolua_tousertype(tolua_S,3,0));
  const AlgVector* w = ((const AlgVector*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Set'",NULL);
#endif
 {
  self->Set(*u,*v,*w);
 }
 }
 return 0;
tolua_lerror:
 return tolua_alg_AlgQuatern_Set01(tolua_S);
}

/* method: Mult of class  AlgQuatern */
static int tolua_alg_AlgQuatern_Mult00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgQuatern",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgQuatern",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgQuatern* self = (AlgQuatern*)  tolua_tousertype(tolua_S,1,0);
  const AlgQuatern* q = ((const AlgQuatern*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Mult'",NULL);
#endif
 {
  self->Mult(*q);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Mult'.",&tolua_err);
 return 0;
#endif
}

/* method: GetAngle of class  AlgQuatern */
static int tolua_alg_AlgQuatern_GetAngle00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgQuatern",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgQuatern* self = (const AlgQuatern*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAngle'",NULL);
#endif
 {
  float tolua_ret = (float)  self->GetAngle();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAngle'.",&tolua_err);
 return 0;
#endif
}

/* method: GetAxis of class  AlgQuatern */
static int tolua_alg_AlgQuatern_GetAxis00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgQuatern",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgQuatern* self = (const AlgQuatern*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetAxis'",NULL);
#endif
 {
  self->GetAxis(&x,&y,&z);
 tolua_pushnumber(tolua_S,(lua_Number)x);
 tolua_pushnumber(tolua_S,(lua_Number)y);
 tolua_pushnumber(tolua_S,(lua_Number)z);
 }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetAxis'.",&tolua_err);
 return 0;
#endif
}

/* method: Get of class  AlgQuatern */
static int tolua_alg_AlgQuatern_Get00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgQuatern",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgQuatern* self = (AlgQuatern*)  tolua_tousertype(tolua_S,1,0);
  AlgVector* u = ((AlgVector*)  tolua_tousertype(tolua_S,2,0));
  AlgVector* v = ((AlgVector*)  tolua_tousertype(tolua_S,3,0));
  AlgVector* w = ((AlgVector*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Get'",NULL);
#endif
 {
  self->Get(u,v,w);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Get'.",&tolua_err);
 return 0;
#endif
}

/* method: Print of class  AlgQuatern */
static int tolua_alg_AlgQuatern_Print00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgQuatern",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgQuatern* self = (AlgQuatern*)  tolua_tousertype(tolua_S,1,0);
  const char* label = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Print'",NULL);
#endif
 {
  self->Print(label);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Print'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  AlgMatrix */
static int tolua_alg_AlgMatrix_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  AlgMatrix* tolua_ret = (AlgMatrix*)  new AlgMatrix();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgMatrix");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  AlgMatrix */
static int tolua_alg_AlgMatrix_new01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_istable(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  float v[16];
 {
#ifndef TOLUA_RELEASE
 if (!tolua_isnumberarray(tolua_S,2,16,0,&tolua_err))
 goto tolua_lerror;
 else
#endif
 {
 int i;
 for(i=0; i<16;i++)
  v[i] = ((float)  tolua_tofieldnumber(tolua_S,2,i+1,0));
 }
 }
 {
  AlgMatrix* tolua_ret = (AlgMatrix*)  new AlgMatrix(v);
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgMatrix");
 }
 {
 int i;
 for(i=0; i<16;i++)
 tolua_pushfieldnumber(tolua_S,2,i+1,(lua_Number) v[i]);
 }
 }
 return 1;
tolua_lerror:
 return tolua_alg_AlgMatrix_new00(tolua_S);
}

/* method: delete of class  AlgMatrix */
static int tolua_alg_AlgMatrix_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
 tolua_release(tolua_S,self);
 delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}

/* method: Identity of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Identity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Identity'",NULL);
#endif
 {
  self->Identity();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Identity'.",&tolua_err);
 return 0;
#endif
}

/* method: Translate of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Translate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Translate'",NULL);
#endif
 {
  self->Translate(x,y,z);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Translate'.",&tolua_err);
 return 0;
#endif
}

/* method: Translate of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Translate01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  const AlgVector* v = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Translate'",NULL);
#endif
 {
  self->Translate(*v);
 }
 }
 return 0;
tolua_lerror:
 return tolua_alg_AlgMatrix_Translate00(tolua_S);
}

/* method: Scale of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Scale00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Scale'",NULL);
#endif
 {
  self->Scale(x,y,z);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Scale'.",&tolua_err);
 return 0;
#endif
}

/* method: Scale of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Scale01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  const AlgVector* v = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Scale'",NULL);
#endif
 {
  self->Scale(*v);
 }
 }
 return 0;
tolua_lerror:
 return tolua_alg_AlgMatrix_Scale00(tolua_S);
}

/* method: Scale of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Scale02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
  float rx = ((float)  tolua_tonumber(tolua_S,5,0));
  float ry = ((float)  tolua_tonumber(tolua_S,6,0));
  float rz = ((float)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Scale'",NULL);
#endif
 {
  self->Scale(x,y,z,rx,ry,rz);
 }
 }
 return 0;
tolua_lerror:
 return tolua_alg_AlgMatrix_Scale01(tolua_S);
}

/* method: Scale of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Scale03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  const AlgVector* v = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
  const AlgVector* r = ((const AlgVector*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Scale'",NULL);
#endif
 {
  self->Scale(*v,*r);
 }
 }
 return 0;
tolua_lerror:
 return tolua_alg_AlgMatrix_Scale02(tolua_S);
}

/* method: Rotate of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Rotate00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float a = ((float)  tolua_tonumber(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
  float z = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rotate'",NULL);
#endif
 {
  self->Rotate(a,x,y,z);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Rotate'.",&tolua_err);
 return 0;
#endif
}

/* method: Rotate of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Rotate01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float a = ((float)  tolua_tonumber(tolua_S,2,0));
  const AlgVector* p = ((const AlgVector*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rotate'",NULL);
#endif
 {
  self->Rotate(a,*p);
 }
 }
 return 0;
tolua_lerror:
 return tolua_alg_AlgMatrix_Rotate00(tolua_S);
}

/* method: Rotate of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Rotate02(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgQuatern",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  const AlgQuatern* q = ((const AlgQuatern*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rotate'",NULL);
#endif
 {
  self->Rotate(*q);
 }
 }
 return 0;
tolua_lerror:
 return tolua_alg_AlgMatrix_Rotate01(tolua_S);
}

/* method: Rotate of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Rotate03(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,8,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,9,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float a = ((float)  tolua_tonumber(tolua_S,2,0));
  float x = ((float)  tolua_tonumber(tolua_S,3,0));
  float y = ((float)  tolua_tonumber(tolua_S,4,0));
  float z = ((float)  tolua_tonumber(tolua_S,5,0));
  float rx = ((float)  tolua_tonumber(tolua_S,6,0));
  float ry = ((float)  tolua_tonumber(tolua_S,7,0));
  float rz = ((float)  tolua_tonumber(tolua_S,8,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rotate'",NULL);
#endif
 {
  self->Rotate(a,x,y,z,rx,ry,rz);
 }
 }
 return 0;
tolua_lerror:
 return tolua_alg_AlgMatrix_Rotate02(tolua_S);
}

/* method: Rotate of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Rotate04(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float a = ((float)  tolua_tonumber(tolua_S,2,0));
  const AlgVector* p = ((const AlgVector*)  tolua_tousertype(tolua_S,3,0));
  const AlgVector* r = ((const AlgVector*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rotate'",NULL);
#endif
 {
  self->Rotate(a,*p,*r);
 }
 }
 return 0;
tolua_lerror:
 return tolua_alg_AlgMatrix_Rotate03(tolua_S);
}

/* method: Rotate of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Rotate05(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgQuatern",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  const AlgQuatern* q = ((const AlgQuatern*)  tolua_tousertype(tolua_S,2,0));
  const AlgVector* r = ((const AlgVector*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Rotate'",NULL);
#endif
 {
  self->Rotate(*q,*r);
 }
 }
 return 0;
tolua_lerror:
 return tolua_alg_AlgMatrix_Rotate04(tolua_S);
}

/* method: LookAt of class  AlgMatrix */
static int tolua_alg_AlgMatrix_LookAt00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,3,"const AlgVector",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,4,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  const AlgVector* pos = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
  const AlgVector* target = ((const AlgVector*)  tolua_tousertype(tolua_S,3,0));
  const AlgVector* up = ((const AlgVector*)  tolua_tousertype(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'LookAt'",NULL);
#endif
 {
  self->LookAt(*pos,*target,*up);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'LookAt'.",&tolua_err);
 return 0;
#endif
}

/* method: Ortho of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Ortho00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float pleft = ((float)  tolua_tonumber(tolua_S,2,0));
  float pright = ((float)  tolua_tonumber(tolua_S,3,0));
  float pbottom = ((float)  tolua_tonumber(tolua_S,4,0));
  float ptop = ((float)  tolua_tonumber(tolua_S,5,0));
  float pnear = ((float)  tolua_tonumber(tolua_S,6,0));
  float pfar = ((float)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Ortho'",NULL);
#endif
 {
  self->Ortho(pleft,pright,pbottom,ptop,pnear,pfar);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Ortho'.",&tolua_err);
 return 0;
#endif
}

/* method: Frustum of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Frustum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,6,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,7,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,8,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float pleft = ((float)  tolua_tonumber(tolua_S,2,0));
  float pright = ((float)  tolua_tonumber(tolua_S,3,0));
  float pbottom = ((float)  tolua_tonumber(tolua_S,4,0));
  float ptop = ((float)  tolua_tonumber(tolua_S,5,0));
  float pnear = ((float)  tolua_tonumber(tolua_S,6,0));
  float pfar = ((float)  tolua_tonumber(tolua_S,7,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Frustum'",NULL);
#endif
 {
  self->Frustum(pleft,pright,pbottom,ptop,pnear,pfar);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Frustum'.",&tolua_err);
 return 0;
#endif
}

/* method: Perspective of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Perspective00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float fovy = ((float)  tolua_tonumber(tolua_S,2,0));
  float aspect = ((float)  tolua_tonumber(tolua_S,3,0));
  float znear = ((float)  tolua_tonumber(tolua_S,4,0));
  float zfar = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Perspective'",NULL);
#endif
 {
  self->Perspective(fovy,aspect,znear,zfar);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Perspective'.",&tolua_err);
 return 0;
#endif
}

/* method: Accum of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Accum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgMatrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  const AlgMatrix* m = ((const AlgMatrix*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Accum'",NULL);
#endif
 {
  self->Accum(*m);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Accum'.",&tolua_err);
 return 0;
#endif
}

/* method: PreAccum of class  AlgMatrix */
static int tolua_alg_AlgMatrix_PreAccum00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgMatrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  const AlgMatrix* m = ((const AlgMatrix*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'PreAccum'",NULL);
#endif
 {
  self->PreAccum(*m);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'PreAccum'.",&tolua_err);
 return 0;
#endif
}

/* method: Transpose of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Transpose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transpose'",NULL);
#endif
 {
  self->Transpose();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Transpose'.",&tolua_err);
 return 0;
#endif
}

/* method: IsIdentity of class  AlgMatrix */
static int tolua_alg_AlgMatrix_IsIdentity00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'IsIdentity'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->IsIdentity();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'IsIdentity'.",&tolua_err);
 return 0;
#endif
}

/* method: Invert of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Invert00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Invert'",NULL);
#endif
 {
  self->Invert();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Invert'.",&tolua_err);
 return 0;
#endif
}

/* method: Inverse of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Inverse00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgMatrix",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgMatrix* self = (const AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Inverse'",NULL);
#endif
 {
  AlgMatrix tolua_ret =  self->Inverse();
 {
#ifdef __cplusplus
 void* tolua_obj = new AlgMatrix(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_AlgMatrix),"AlgMatrix");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AlgMatrix));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"AlgMatrix");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Inverse'.",&tolua_err);
 return 0;
#endif
}

/* method: Transform of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Transform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgMatrix* self = (const AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float x = ((float)  tolua_tonumber(tolua_S,2,0));
  float y = ((float)  tolua_tonumber(tolua_S,3,0));
  float z = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transform'",NULL);
#endif
 {
  AlgVector tolua_ret =  self->Transform(x,y,z);
 {
#ifdef __cplusplus
 void* tolua_obj = new AlgVector(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_AlgVector),"AlgVector");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AlgVector));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"AlgVector");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Transform'.",&tolua_err);
 return 0;
#endif
}

/* method: Transform of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Transform01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgMatrix",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const AlgMatrix* self = (const AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  const AlgVector* p = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Transform'",NULL);
#endif
 {
  AlgVector tolua_ret =  self->Transform(*p);
 {
#ifdef __cplusplus
 void* tolua_obj = new AlgVector(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_AlgVector),"AlgVector");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AlgVector));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"AlgVector");
#endif
 }
 }
 }
 return 1;
tolua_lerror:
 return tolua_alg_AlgMatrix_Transform00(tolua_S);
}

/* method: TransformVector of class  AlgMatrix */
static int tolua_alg_AlgMatrix_TransformVector00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgMatrix",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgMatrix* self = (const AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  float vx = ((float)  tolua_tonumber(tolua_S,2,0));
  float vy = ((float)  tolua_tonumber(tolua_S,3,0));
  float vz = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TransformVector'",NULL);
#endif
 {
  AlgVector tolua_ret =  self->TransformVector(vx,vy,vz);
 {
#ifdef __cplusplus
 void* tolua_obj = new AlgVector(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_AlgVector),"AlgVector");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AlgVector));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"AlgVector");
#endif
 }
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'TransformVector'.",&tolua_err);
 return 0;
#endif
}

/* method: TransformVector of class  AlgMatrix */
static int tolua_alg_AlgMatrix_TransformVector01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgMatrix",0,&tolua_err) ||
 !tolua_isusertype(tolua_S,2,"const AlgVector",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
 {
  const AlgMatrix* self = (const AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  const AlgVector* v = ((const AlgVector*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'TransformVector'",NULL);
#endif
 {
  AlgVector tolua_ret =  self->TransformVector(*v);
 {
#ifdef __cplusplus
 void* tolua_obj = new AlgVector(tolua_ret);
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,tolua_collect_AlgVector),"AlgVector");
#else
 void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(AlgVector));
 tolua_pushusertype(tolua_S,tolua_clone(tolua_S,tolua_obj,NULL),"AlgVector");
#endif
 }
 }
 }
 return 1;
tolua_lerror:
 return tolua_alg_AlgMatrix_TransformVector00(tolua_S);
}

/* method: Print of class  AlgMatrix */
static int tolua_alg_AlgMatrix_Print00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"const AlgMatrix",0,&tolua_err) ||
 !tolua_isstring(tolua_S,2,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  const AlgMatrix* self = (const AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  const char* label = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Print'",NULL);
#endif
 {
  self->Print(label);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Print'.",&tolua_err);
 return 0;
#endif
}

/* method: GetMatrixDouble of class  AlgMatrix */
static int tolua_alg_AlgMatrix_GetMatrix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgMatrix",0,&tolua_err) ||
 !tolua_istable(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgMatrix* self = (AlgMatrix*)  tolua_tousertype(tolua_S,1,0);
  double v[16];
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetMatrixDouble'",NULL);
#endif
 {
#ifndef TOLUA_RELEASE
 if (!tolua_isnumberarray(tolua_S,2,16,1,&tolua_err))
 goto tolua_lerror;
 else
#endif
 {
 int i;
 for(i=0; i<16;i++)
  v[i] = ((double)  tolua_tofieldnumber(tolua_S,2,i+1,0));
 }
 }
 {
  self->GetMatrixDouble(v);
 }
 {
 int i;
 for(i=0; i<16;i++)
 tolua_pushfieldnumber(tolua_S,2,i+1,(lua_Number) v[i]);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetMatrix'.",&tolua_err);
 return 0;
#endif
}

/* method: new of class  AlgSpline */
static int tolua_alg_AlgSpline_new00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertable(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
 {
  AlgSpline* tolua_ret = (AlgSpline*)  new AlgSpline();
 tolua_pushusertype(tolua_S,(void*)tolua_ret,"AlgSpline");
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'new'.",&tolua_err);
 return 0;
#endif
}

/* method: delete of class  AlgSpline */
static int tolua_alg_AlgSpline_delete00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delete'",NULL);
#endif
 tolua_release(tolua_S,self);
 delete self;
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delete'.",&tolua_err);
 return 0;
#endif
}

/* method: SetDefaultTension of class  AlgSpline */
static int tolua_alg_AlgSpline_SetDefaultTension00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  double v = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetDefaultTension'",NULL);
#endif
 {
  self->SetDefaultTension(v);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetDefaultTension'.",&tolua_err);
 return 0;
#endif
}

/* method: SetAutoKnotMethod of class  AlgSpline */
static int tolua_alg_AlgSpline_SetAutoKnotMethod00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  int autoknot = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetAutoKnotMethod'",NULL);
#endif
 {
  self->SetAutoKnotMethod(autoknot);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetAutoKnotMethod'.",&tolua_err);
 return 0;
#endif
}

/* method: Begin of class  AlgSpline */
static int tolua_alg_AlgSpline_Begin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Begin'",NULL);
#endif
 {
  self->Begin();
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Begin'.",&tolua_err);
 return 0;
#endif
}

/* method: AddPosition of class  AlgSpline */
static int tolua_alg_AlgSpline_AddPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  double x = ((double)  tolua_tonumber(tolua_S,2,0));
  double y = ((double)  tolua_tonumber(tolua_S,3,0));
  double z = ((double)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'AddPosition'",NULL);
#endif
 {
  self->AddPosition(x,y,z);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'AddPosition'.",&tolua_err);
 return 0;
#endif
}

/* method: SetTension of class  AlgSpline */
static int tolua_alg_AlgSpline_SetTension00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  double v = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetTension'",NULL);
#endif
 {
  self->SetTension(v);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetTension'.",&tolua_err);
 return 0;
#endif
}

/* method: SetKnot of class  AlgSpline */
static int tolua_alg_AlgSpline_SetKnot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  double t = ((double)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'SetKnot'",NULL);
#endif
 {
  self->SetKnot(t);
 }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'SetKnot'.",&tolua_err);
 return 0;
#endif
}

/* method: End of class  AlgSpline */
static int tolua_alg_AlgSpline_End00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'End'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->End();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'End'.",&tolua_err);
 return 0;
#endif
}

/* method: ModifyPosition of class  AlgSpline */
static int tolua_alg_AlgSpline_ModifyPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
  double x = ((double)  tolua_tonumber(tolua_S,3,0));
  double y = ((double)  tolua_tonumber(tolua_S,4,0));
  double z = ((double)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ModifyPosition'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->ModifyPosition(i,x,y,z);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ModifyPosition'.",&tolua_err);
 return 0;
#endif
}

/* method: ModifyKnot of class  AlgSpline */
static int tolua_alg_AlgSpline_ModifyKnot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
  double t = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ModifyKnot'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->ModifyKnot(i,t);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ModifyKnot'.",&tolua_err);
 return 0;
#endif
}

/* method: ModifyTension of class  AlgSpline */
static int tolua_alg_AlgSpline_ModifyTension00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
  double v = ((double)  tolua_tonumber(tolua_S,3,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'ModifyTension'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->ModifyTension(i,v);
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'ModifyTension'.",&tolua_err);
 return 0;
#endif
}

/* method: Recompute of class  AlgSpline */
static int tolua_alg_AlgSpline_Recompute00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'Recompute'",NULL);
#endif
 {
  bool tolua_ret = (bool)  self->Recompute();
 tolua_pushboolean(tolua_S,(bool)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'Recompute'.",&tolua_err);
 return 0;
#endif
}

/* method: GetPosition of class  AlgSpline */
static int tolua_alg_AlgSpline_GetPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  double t = ((double)  tolua_tonumber(tolua_S,2,0));
  double x = ((double)  tolua_tonumber(tolua_S,3,0));
  double y = ((double)  tolua_tonumber(tolua_S,4,0));
  double z = ((double)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetPosition'",NULL);
#endif
 {
  self->GetPosition(t,&x,&y,&z);
 tolua_pushnumber(tolua_S,(lua_Number)x);
 tolua_pushnumber(tolua_S,(lua_Number)y);
 tolua_pushnumber(tolua_S,(lua_Number)z);
 }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetPosition'.",&tolua_err);
 return 0;
#endif
}

/* method: GetNSegments of class  AlgSpline */
static int tolua_alg_AlgSpline_GetNSegments00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNSegments'",NULL);
#endif
 {
  int tolua_ret = (int)  self->GetNSegments();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNSegments'.",&tolua_err);
 return 0;
#endif
}

/* method: GetNPositions of class  AlgSpline */
static int tolua_alg_AlgSpline_GetNPositions00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetNPositions'",NULL);
#endif
 {
  int tolua_ret = (int)  self->GetNPositions();
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetNPositions'.",&tolua_err);
 return 0;
#endif
}

/* method: GetGivenPosition of class  AlgSpline */
static int tolua_alg_AlgSpline_GetGivenPosition00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnumber(tolua_S,3,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
 !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
 !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
  double x = ((double)  tolua_tonumber(tolua_S,3,0));
  double y = ((double)  tolua_tonumber(tolua_S,4,0));
  double z = ((double)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetGivenPosition'",NULL);
#endif
 {
  self->GetGivenPosition(i,&x,&y,&z);
 tolua_pushnumber(tolua_S,(lua_Number)x);
 tolua_pushnumber(tolua_S,(lua_Number)y);
 tolua_pushnumber(tolua_S,(lua_Number)z);
 }
 }
 return 3;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetGivenPosition'.",&tolua_err);
 return 0;
#endif
}

/* method: GetKnot of class  AlgSpline */
static int tolua_alg_AlgSpline_GetKnot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetKnot'",NULL);
#endif
 {
  double tolua_ret = (double)  self->GetKnot(i);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetKnot'.",&tolua_err);
 return 0;
#endif
}

/* method: GetTension of class  AlgSpline */
static int tolua_alg_AlgSpline_GetTension00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
 !tolua_isusertype(tolua_S,1,"AlgSpline",0,&tolua_err) ||
 !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
 !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
 goto tolua_lerror;
 else
#endif
 {
  AlgSpline* self = (AlgSpline*)  tolua_tousertype(tolua_S,1,0);
  int i = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
 if (!self) tolua_error(tolua_S,"invalid 'self' in function 'GetTension'",NULL);
#endif
 {
  double tolua_ret = (double)  self->GetTension(i);
 tolua_pushnumber(tolua_S,(lua_Number)tolua_ret);
 }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'GetTension'.",&tolua_err);
 return 0;
#endif
}

/* Open function */
TOLUA_API int tolua_alg_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"AlgVector","AlgVector","",tolua_collect_AlgVector);
#else
 tolua_cclass(tolua_S,"AlgVector","AlgVector","",NULL);
#endif
 tolua_beginmodule(tolua_S,"AlgVector");
 tolua_variable(tolua_S,"x",tolua_get_AlgVector_AlgVector_x,tolua_set_AlgVector_AlgVector_x);
 tolua_variable(tolua_S,"y",tolua_get_AlgVector_AlgVector_y,tolua_set_AlgVector_AlgVector_y);
 tolua_variable(tolua_S,"z",tolua_get_AlgVector_AlgVector_z,tolua_set_AlgVector_AlgVector_z);
 tolua_function(tolua_S,"new",tolua_alg_AlgVector_new00);
 tolua_function(tolua_S,"new",tolua_alg_AlgVector_new01);
 tolua_function(tolua_S,"delete",tolua_alg_AlgVector_delete00);
 tolua_function(tolua_S,"Set",tolua_alg_AlgVector_Set00);
 tolua_function(tolua_S,"Dot",tolua_alg_AlgVector_Dot00);
 tolua_function(tolua_S,"Cross",tolua_alg_AlgVector_Cross00);
 tolua_function(tolua_S,"Length",tolua_alg_AlgVector_Length00);
 tolua_function(tolua_S,"Normalize",tolua_alg_AlgVector_Normalize00);
 tolua_function(tolua_S,"Print",tolua_alg_AlgVector_Print00);
 tolua_endmodule(tolua_S);
 tolua_function(tolua_S,"Intersect",tolua_alg_Intersect00);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"AlgPlane","AlgPlane","",tolua_collect_AlgPlane);
#else
 tolua_cclass(tolua_S,"AlgPlane","AlgPlane","",NULL);
#endif
 tolua_beginmodule(tolua_S,"AlgPlane");
 tolua_function(tolua_S,"new",tolua_alg_AlgPlane_new00);
 tolua_function(tolua_S,"new",tolua_alg_AlgPlane_new01);
 tolua_function(tolua_S,"new",tolua_alg_AlgPlane_new02);
 tolua_function(tolua_S,"delete",tolua_alg_AlgPlane_delete00);
 tolua_function(tolua_S,"Set",tolua_alg_AlgPlane_Set00);
 tolua_function(tolua_S,"GetNormal",tolua_alg_AlgPlane_GetNormal00);
 tolua_function(tolua_S,"Normalize",tolua_alg_AlgPlane_Normalize00);
 tolua_function(tolua_S,"Distance",tolua_alg_AlgPlane_Distance00);
 tolua_function(tolua_S,"Print",tolua_alg_AlgPlane_Print00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"AlgQuatern","AlgQuatern","",tolua_collect_AlgQuatern);
#else
 tolua_cclass(tolua_S,"AlgQuatern","AlgQuatern","",NULL);
#endif
 tolua_beginmodule(tolua_S,"AlgQuatern");
 tolua_function(tolua_S,"new",tolua_alg_AlgQuatern_new00);
 tolua_function(tolua_S,"new",tolua_alg_AlgQuatern_new01);
 tolua_function(tolua_S,"new",tolua_alg_AlgQuatern_new02);
 tolua_function(tolua_S,"new",tolua_alg_AlgQuatern_new03);
 tolua_function(tolua_S,"delete",tolua_alg_AlgQuatern_delete00);
 tolua_function(tolua_S,"Set",tolua_alg_AlgQuatern_Set00);
 tolua_function(tolua_S,"Set",tolua_alg_AlgQuatern_Set01);
 tolua_function(tolua_S,"Set",tolua_alg_AlgQuatern_Set02);
 tolua_function(tolua_S,"Mult",tolua_alg_AlgQuatern_Mult00);
 tolua_function(tolua_S,"GetAngle",tolua_alg_AlgQuatern_GetAngle00);
 tolua_function(tolua_S,"GetAxis",tolua_alg_AlgQuatern_GetAxis00);
 tolua_function(tolua_S,"Get",tolua_alg_AlgQuatern_Get00);
 tolua_function(tolua_S,"Print",tolua_alg_AlgQuatern_Print00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"AlgMatrix","AlgMatrix","",tolua_collect_AlgMatrix);
#else
 tolua_cclass(tolua_S,"AlgMatrix","AlgMatrix","",NULL);
#endif
 tolua_beginmodule(tolua_S,"AlgMatrix");
 tolua_function(tolua_S,"new",tolua_alg_AlgMatrix_new00);
 tolua_function(tolua_S,"new",tolua_alg_AlgMatrix_new01);
 tolua_function(tolua_S,"delete",tolua_alg_AlgMatrix_delete00);
 tolua_function(tolua_S,"Identity",tolua_alg_AlgMatrix_Identity00);
 tolua_function(tolua_S,"Translate",tolua_alg_AlgMatrix_Translate00);
 tolua_function(tolua_S,"Translate",tolua_alg_AlgMatrix_Translate01);
 tolua_function(tolua_S,"Scale",tolua_alg_AlgMatrix_Scale00);
 tolua_function(tolua_S,"Scale",tolua_alg_AlgMatrix_Scale01);
 tolua_function(tolua_S,"Scale",tolua_alg_AlgMatrix_Scale02);
 tolua_function(tolua_S,"Scale",tolua_alg_AlgMatrix_Scale03);
 tolua_function(tolua_S,"Rotate",tolua_alg_AlgMatrix_Rotate00);
 tolua_function(tolua_S,"Rotate",tolua_alg_AlgMatrix_Rotate01);
 tolua_function(tolua_S,"Rotate",tolua_alg_AlgMatrix_Rotate02);
 tolua_function(tolua_S,"Rotate",tolua_alg_AlgMatrix_Rotate03);
 tolua_function(tolua_S,"Rotate",tolua_alg_AlgMatrix_Rotate04);
 tolua_function(tolua_S,"Rotate",tolua_alg_AlgMatrix_Rotate05);
 tolua_function(tolua_S,"LookAt",tolua_alg_AlgMatrix_LookAt00);
 tolua_function(tolua_S,"Ortho",tolua_alg_AlgMatrix_Ortho00);
 tolua_function(tolua_S,"Frustum",tolua_alg_AlgMatrix_Frustum00);
 tolua_function(tolua_S,"Perspective",tolua_alg_AlgMatrix_Perspective00);
 tolua_function(tolua_S,"Accum",tolua_alg_AlgMatrix_Accum00);
 tolua_function(tolua_S,"PreAccum",tolua_alg_AlgMatrix_PreAccum00);
 tolua_function(tolua_S,"Transpose",tolua_alg_AlgMatrix_Transpose00);
 tolua_function(tolua_S,"IsIdentity",tolua_alg_AlgMatrix_IsIdentity00);
 tolua_function(tolua_S,"Invert",tolua_alg_AlgMatrix_Invert00);
 tolua_function(tolua_S,"Inverse",tolua_alg_AlgMatrix_Inverse00);
 tolua_function(tolua_S,"Transform",tolua_alg_AlgMatrix_Transform00);
 tolua_function(tolua_S,"Transform",tolua_alg_AlgMatrix_Transform01);
 tolua_function(tolua_S,"TransformVector",tolua_alg_AlgMatrix_TransformVector00);
 tolua_function(tolua_S,"TransformVector",tolua_alg_AlgMatrix_TransformVector01);
 tolua_function(tolua_S,"Print",tolua_alg_AlgMatrix_Print00);
 tolua_function(tolua_S,"GetMatrix",tolua_alg_AlgMatrix_GetMatrix00);
 tolua_endmodule(tolua_S);
#ifdef __cplusplus
 tolua_cclass(tolua_S,"AlgSpline","AlgSpline","",tolua_collect_AlgSpline);
#else
 tolua_cclass(tolua_S,"AlgSpline","AlgSpline","",NULL);
#endif
 tolua_beginmodule(tolua_S,"AlgSpline");
 tolua_function(tolua_S,"new",tolua_alg_AlgSpline_new00);
 tolua_function(tolua_S,"delete",tolua_alg_AlgSpline_delete00);
 tolua_function(tolua_S,"SetDefaultTension",tolua_alg_AlgSpline_SetDefaultTension00);
 tolua_function(tolua_S,"SetAutoKnotMethod",tolua_alg_AlgSpline_SetAutoKnotMethod00);
 tolua_function(tolua_S,"Begin",tolua_alg_AlgSpline_Begin00);
 tolua_function(tolua_S,"AddPosition",tolua_alg_AlgSpline_AddPosition00);
 tolua_function(tolua_S,"SetTension",tolua_alg_AlgSpline_SetTension00);
 tolua_function(tolua_S,"SetKnot",tolua_alg_AlgSpline_SetKnot00);
 tolua_function(tolua_S,"End",tolua_alg_AlgSpline_End00);
 tolua_function(tolua_S,"ModifyPosition",tolua_alg_AlgSpline_ModifyPosition00);
 tolua_function(tolua_S,"ModifyKnot",tolua_alg_AlgSpline_ModifyKnot00);
 tolua_function(tolua_S,"ModifyTension",tolua_alg_AlgSpline_ModifyTension00);
 tolua_function(tolua_S,"Recompute",tolua_alg_AlgSpline_Recompute00);
 tolua_function(tolua_S,"GetPosition",tolua_alg_AlgSpline_GetPosition00);
 tolua_function(tolua_S,"GetNSegments",tolua_alg_AlgSpline_GetNSegments00);
 tolua_function(tolua_S,"GetNPositions",tolua_alg_AlgSpline_GetNPositions00);
 tolua_function(tolua_S,"GetGivenPosition",tolua_alg_AlgSpline_GetGivenPosition00);
 tolua_function(tolua_S,"GetKnot",tolua_alg_AlgSpline_GetKnot00);
 tolua_function(tolua_S,"GetTension",tolua_alg_AlgSpline_GetTension00);
 tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}
