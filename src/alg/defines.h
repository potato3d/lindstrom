#ifndef ALG_DEFINES_H
#define ALG_DEFINES_H

#ifdef ALG_DLL
 #define ALG_API __declspec(dllexport)
#else
 #define ALG_API
#endif

#define ALG_TOL 1.0e-7
#define ALG_PI 3.14159f

#if (defined(_WIN32) && !defined(HAS_POSIX))
# include <float.h>
# define ALG_FINITE(a) _finite(a)
#elif defined(__sun)
# include <ieeefp.h>
# define ALG_FINITE(a) finite(a)
#else
# include <math.h>
# define ALG_FINITE(a) finite(a)
#endif

#endif
