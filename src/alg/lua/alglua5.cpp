extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <tolua.h>
}
#include "alglua.h"
#include "algtolua5.h"

ALGLUAAPI int alg_open (lua_State* L)
{
  return tolua_alg_open(L);
}
