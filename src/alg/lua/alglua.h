#ifndef ALG_LUA
#define ALG_LUA

#ifdef __cplusplus
extern "C" {
#endif
#include <lua.h>
#ifdef __cplusplus
}

# ifdef _WIN32
#  ifdef ALGLUA_DLL
#   define ALGLUAAPI extern "C" __declspec(dllexport)
#  else
#   define ALGLUAAPI extern "C"
#  endif
# else
#  define ALGLUAAPI extern "C" 
# endif
#else
# define ALGLUAAPI
#endif

#ifdef LUA_NOOBJECT  /* Lua 3 */
ALGLUAAPI int  alg_open   (void);
ALGLUAAPI void alg_close  (void);
#endif
#ifdef LUA_NOREF  /* Lua 4 or 5 */
ALGLUAAPI int  alg_open   (lua_State* L);
ALGLUAAPI void alg_close  (lua_State* L);
#endif

#endif
