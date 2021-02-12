#ifndef TERRAIN_DEFINES
#define TERRAIN_DEFINES

/*
** mathematical defines
*/
#define DEG2RAD(x)      ((3.1415927f / 180.0f) * (x))
#define RAD2DEG(x)      ((180.0f / 3.1415927f) * (x))
#define MIN(a, b)       ((a) < (b) ? (a) : (b))
#define MAX(a, b)       ((a) > (b) ? (a) : (b))
#define ISPOW2(x)       (!((x) & ((x) - 1)) && !!(x))
#define SQR(x)          ((x) * (x))
#define DISTANCE_SQR(p, q)  (SQR((p)->x-(q)->x) + SQR((p)->y-(q)->y) + SQR((p)->z-(q)->z))
#define DISTANCE_SQR2(p, qx, qy, qz)  (SQR((p)->x-(qx)) + SQR((p)->y-(qy)) + SQR((p)->z-(qz)))
#define DISTANCE_SQR3(p, qx, qy, qz)  (SQR((p)->x-(qx)) + SQR((p)->height-(qy)) + SQR((p)->z-(qz)))
#define DISTANCE(p, q)  (sqrtf(DISTANCE_SQR(p, q)))
#define CROSS_PRODUCT(x, y, z) ((void)((x)[0] = (y)[1]*(z)[2] - (y)[2]*(z)[1], (x)[1] = (y)[2]*(z)[0] - (y)[0]*(z)[2], (x)[2] = (y)[0]*(z)[1] - (y)[1]*(z)[0]))
#define ADD(x, y) ((void)((x)[0] += (y)[0], (x)[1] += (y)[1], (x)[2] += (y)[2]))

#define ALL_PLANES_VISIBLE 0x007Fu
#define INITIAL_VISIBILITY 0x0040u

/*
** Index Computation Defines
*/

#define LN_INDEX(i, j, m)         ((i) + (j) + ((j) << (m)))
#define LN_SPLIT(i, j, k)         (((j) + (k)) / 2)
#define LN_CHILD_LEFT(i, j, k)    LN_SPLIT(i, j, k), j, i
#define LN_CHILD_RIGHT(i, j, k)   LN_SPLIT(i, j, k), i, k

#define IQ_SPLIT(i, j)       (j)
#define IQ_CHILD_LEFT(i, j)  IQ_SPLIT(i, j), (4*(i)-7 + ((2*(i)+(j)+2) & 3))
#define IQ_CHILD_RIGHT(i, j) IQ_SPLIT(i, j), (4*(i)-7 + ((2*(i)+(j)+3) & 3))

#define COUNT_ONE_DIM(n)       (1 << ((n) / 2)) + 1

#define LINEAR_INDEXING               1
#define INTERLEAVED_QUADTREE_INDEXING 2

// definitions for LINEAR_INDEXING
#define LN_COUNT(n)               SQR(COUNT_ONE_DIM(n))

#define LN_I_SW(m)               LN_INDEX(0 << (m), 0 << (m), m)
#define LN_I_SE(m)               LN_INDEX(1 << (m), 0 << (m), m)
#define LN_I_NE(m)               LN_INDEX(1 << (m), 1 << (m), m)
#define LN_I_NW(m)               LN_INDEX(0 << (m), 1 << (m), m)
#define LN_I_C(m)                LN_INDEX(1 << ((m) - 1), 1 << ((m) - 1), m)
#define LN_I_S(m)                LN_INDEX(1 << ((m) - 1), 0 << (m), m)
#define LN_I_E(m)                LN_INDEX(1 << (m), 1 << ((m) - 1), m)
#define LN_I_N(m)                LN_INDEX(1 << ((m) - 1), 1 << (m), m)
#define LN_I_W(m)                LN_INDEX(0 << (m), 1 << ((m) - 1), m)
#define LN_ROOT_S(m)             LN_I_C(m), LN_I_SW(m), LN_I_SE(m)
#define LN_ROOT_E(m)             LN_I_C(m), LN_I_SE(m), LN_I_NE(m)
#define LN_ROOT_N(m)             LN_I_C(m), LN_I_NE(m), LN_I_NW(m)
#define LN_ROOT_W(m)             LN_I_C(m), LN_I_NW(m), LN_I_SW(m)

#define LN_SPLIT_ROOT_S(m)       LN_SPLIT(LN_I_C(m), LN_I_SW(m), LN_I_SE(m))
#define LN_SPLIT_ROOT_E(m)       LN_SPLIT(LN_I_C(m), LN_I_SE(m), LN_I_NE(m))
#define LN_SPLIT_ROOT_N(m)       LN_SPLIT(LN_I_C(m), LN_I_NE(m), LN_I_NW(m))
#define LN_SPLIT_ROOT_W(m)       LN_SPLIT(LN_I_C(m), LN_I_NW(m), LN_I_SW(m))

#define LN_SPLIT_CHILD_LEFT(i, j, k)  LN_SPLIT(LN_SPLIT(i, j, k), j, i)
#define LN_SPLIT_CHILD_RIGHT(i, j, k) LN_SPLIT(LN_SPLIT(i, j, k), i, k)

/*
#define TRIANGLE(i, j, k)     i, j, k
#define TO_TRIANGLE(i, j, k)  i, j, k
#define TRIANGLE_CMD(i, j, k) i j k
*/
#define LN_CHILD_LEFT_TRI(i, j, k)        LN_SPLIT(i, j, k), i, j
#define LN_CHILD_RIGHT_TRI(i, j, k)       LN_SPLIT(i, j, k), k, i
#define LN_SPLIT_CHILD_LEFT_TRI(i, j, k)  LN_SPLIT(LN_SPLIT(i, j, k), i, j)
#define LN_SPLIT_CHILD_RIGHT_TRI(i, j, k) LN_SPLIT(LN_SPLIT(i, j, k), k, i)

//definitions for INTERLEAVED_QUADTREE_INDEXING
#define IQ_COUNT(n)             (4 + 5 * ((1 << (n)) - 1) / 3)

#define IQ_I_SW(m)               0
#define IQ_I_SE(m)               1
#define IQ_I_NE(m)               2
#define IQ_I_NW(m)               3
#define IQ_I_C(m)                4
#define IQ_I_W(m)                5
#define IQ_I_S(m)                6
#define IQ_I_E(m)                7
#define IQ_I_N(m)                8

#define IQ_ROOT_S(m)             IQ_I_C(m), IQ_I_S(m)
#define IQ_ROOT_E(m)             IQ_I_C(m), IQ_I_E(m)
#define IQ_ROOT_N(m)             IQ_I_C(m), IQ_I_N(m)
#define IQ_ROOT_W(m)             IQ_I_C(m), IQ_I_W(m)

#define IQ_ROOT_S_TRI(m)         IQ_I_C(m), IQ_I_S(m), IQ_I_SW(m), IQ_I_SE(m)
#define IQ_ROOT_E_TRI(m)         IQ_I_C(m), IQ_I_E(m), IQ_I_SE(m), IQ_I_NE(m)
#define IQ_ROOT_N_TRI(m)         IQ_I_C(m), IQ_I_N(m), IQ_I_NE(m), IQ_I_NW(m)
#define IQ_ROOT_W_TRI(m)         IQ_I_C(m), IQ_I_W(m), IQ_I_NW(m), IQ_I_SW(m)


#define IQ_SPLIT_ROOT_S(m)       IQ_SPLIT(IQ_I_C(m), IQ_I_S(m))
#define IQ_SPLIT_ROOT_E(m)       IQ_SPLIT(IQ_I_C(m), IQ_I_E(m))
#define IQ_SPLIT_ROOT_N(m)       IQ_SPLIT(IQ_I_C(m), IQ_I_N(m))
#define IQ_SPLIT_ROOT_W(m)       IQ_SPLIT(IQ_I_C(m), IQ_I_W(m))
/*
#define TRIANGLE(i, j, k)     i, j
#define TO_TRIANGLE(i, j, k)  i, j, j
#define TRIANGLE_CMD(i, j, k) i j

#define IQ_CHILD_LEFT_TRI(i, j, k)        IQ_CHILD_LEFT(i, j, k)
#define IQ_CHILD_RIGHT_TRI(i, j, k)       IQ_CHILD_RIGHT(i, j, k)
*/
#define IQ_SPLIT_CHILD_LEFT(i, j)  IQ_SPLIT(IQ_SPLIT(i, j), (4*(i)-7 + ((2*(i)+(j)+2) & 3))) //SPLIT(IQ_CHILD_LEFT(i, j))
#define IQ_SPLIT_CHILD_RIGHT(i, j) IQ_SPLIT(IQ_SPLIT(i, j), (4*(i)-7 + ((2*(i)+(j)+3) & 3))) //SPLIT(IQ_CHILD_RIGHT(i, j))

/*
** Terrain defines
*/
#define MIN_LEVEL 2

#endif
