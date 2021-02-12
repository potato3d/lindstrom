extern "C" {
#include <lua.h>
#include <lauxlib.h>
}
#include "alglua.h"
#include "algtolua4.h"

int ALGLUAAPI alg_open (lua_State* L)
{
  int r = tolua_alg_open(L);
//#include "constructors5.c"
  return r;
}
