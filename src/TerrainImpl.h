#ifndef TERRAIN_IMPL_INCLUDED
#define TERRAIN_IMPL_INCLUDED

//class Rnd;
class AlgVector;
#include "Defines.h"
#include <math.h>
#include <float.h>

struct plane
{
  float a, b, c, d;
};

struct viewPlanes
{
enum plane_visibility{
	   NOT_VISIBLE = 0,
       LEFT_VISIBLE = 1,
	   RIGHT_VISIBLE = 2,
	   NEAR_VISIBLE = 4,
	   FAR_VISIBLE = 8,
	   BOTTON_VISIBLE = 16,
	   TOP_VISIBLE = 32
	 };
  plane viewplane[6];
  unsigned int   isInside;
};

struct viewParameters
{
  float position_x;            /* view x position */
  float position_y;            /* view y position */
  float position_z;            /* view z position */
  float invErrorTolerance;     /* view dependent screen space error tolerance inverted */
  float invErrorTolerance_min; /* minimum error tolerance - for morphing */
  float invErrorTolerance_max; /* maximum error tolerance - for morphing */
  float lambda;

  int   cullEnabled;
  viewPlanes planes;
};

class TerrainImpl
{
  friend class Terrain;
  friend class TerrainNormals;
  friend class TerrainTiledImpl;
protected:
  struct vertexData
  {
    float x, y, z;  /* vertex position */
	float height;   /* original height - y coordinate */
    float e;        /* vertex object space error */
    float r;        /* vertex bounding radius */
  };

public:
  typedef void (*PROGRESS_CALLBACK)(void*, float);

  TerrainImpl();
  ~TerrainImpl();

// Client Functions
  int LoadFromImage(const char* filename, 
				    const float origin_x = 0, const float origin_y = 0, const float origin_z = 0,
					const float scale_x = 1 , const float scale_y = 1 , const float scale_z = 1);

  int Load(const char* filename,
	       bool outOfCore);
  int Save(const char* filename);

  int PreProcess();
  unsigned int DataReindex();

  //void Render(viewParameters view, 
	 //         Rnd* renderer);

  int GetIndexing() { return m_indexing; }
  void SetProgressCallback(PROGRESS_CALLBACK cb, void* data);

  bool GetHeight(float x, float z, float* height);
  const char* GetErrorMsg() {return m_errorMsg;}
  void GetBBox(float *x_min, float *y_min, float *z_min,
	           float *x_max, float *y_max, float *z_max) const;

// Inline Functions
  inline float* GetVertexPointer() { return (float*) m_vertices; }
  inline int GetVertexOffset() { return sizeof(TerrainImpl::vertexData); }

  inline float* GetVertexPos(unsigned int i) { return &m_vertices[i].x; }
  inline float GetVertexPosX(unsigned int i) { return m_vertices[i].x; }
  inline float GetVertexPosX(float* v) { return ((TerrainImpl::vertexData *)v)->x; }
  inline float GetVertexPosY(unsigned int i) { return m_vertices[i].y; }
  inline float GetVertexPosY(float* v) { return ((TerrainImpl::vertexData *)v)->y; }
  inline float GetVertexHeight(unsigned int i) { return m_vertices[i].height; }
  inline float GetVertexHeight(float* v) { return ((TerrainImpl::vertexData *)v)->height; }
  inline float GetVertexPosZ(unsigned int i) { return m_vertices[i].z; }
  inline float GetVertexPosZ(float* v) { return ((TerrainImpl::vertexData *)v)->z; }
  inline float GetVertexError(unsigned int i) { return m_vertices[i].e; }
  inline float GetVertexError(float* v) { return ((TerrainImpl::vertexData *)v)->e; }
  inline float GetVertexRadius(unsigned int i) { return m_vertices[i].r; }
  inline float GetVertexRadius(float* v) { return ((TerrainImpl::vertexData *)v)->r; }
  inline int GetLevels() { return m_levels; }
  inline int GetSize() { return m_size; }

  inline int VertexActive(unsigned int i, const viewParameters* view)
  {
    vertexData* v = &m_vertices[i];
	return SQR(view->invErrorTolerance*v->e + v->r) > DISTANCE_SQR2(v, view->position_x, view->position_y, view->position_z);
  }

  inline float VertexTauSphere(unsigned int i, const viewParameters* view)
  {
    vertexData* v = &m_vertices[i];
	return view->invErrorTolerance*v->e + v->r;
  }

  inline int VertexError(unsigned int i, const viewParameters* view, float &error)
  {
    vertexData* v = &m_vertices[i];
	error = view->lambda*v->e / (sqrtf(DISTANCE_SQR2(v, view->position_x, view->position_y, view->position_z)) - v->r);
//	error = view.lambda*v->e / (sqrtf(DISTANCE_SQR2(v, view.position_x, view.position_y, view.position_z)) + v->r);
//	error = view.lambda*v->e / (sqrtf(DISTANCE_SQR2(v, view.position_x, view.position_y, view.position_z)));
//	error = view.lambda*v->e / (DISTANCE_SQR2(v, view.position_x, view.position_y, view.position_z) - v->r);

//	error = SQR(view.invErrorTolerance*v->e + v->r) - DISTANCE_SQR2(v, view.position_x, view.position_y, view.position_z);
//	error = view.invErrorTolerance*v->e + v->r - sqrt(DISTANCE_SQR2(v, view.position_x, view.position_y, view.position_z));
//	error = view.invErrorTolerance*v->e + v->r;
	if (error < 0) error = FLT_MAX;
	return error > 0;
  }

  inline float VertexDistanceSquare(unsigned int i, const viewParameters* view)
  {
    vertexData* v = &m_vertices[i];
    return DISTANCE_SQR2(v, view->position_x, view->position_y, view->position_z);
  }

  inline int IsSphereVisible(unsigned int p, unsigned int mask, viewParameters* view)
  {
    vertexData* v = &m_vertices[p];
	for (int i = 0; i < 6; i++)
	{
	  if (!(mask & (1u << i)))
	  {
		plane* currPlane = &view->planes.viewplane[i];
		float dist = v->x*currPlane->a + v->y*currPlane->b + v->z*currPlane->c + currPlane->d;
//		float dist = v->x*view.planes.viewplane[i].a + v->height*view.planes.viewplane[i].b + v->z*view.planes.viewplane[i].c + view.planes.viewplane[i].d;

		if (dist < -v->r) // Totally outside
		  return 0;		  
		if (dist > v->r) // Totally inside
		  mask |= 1u << i;

/*
		if ((dist - v->r) > 0) // Totally outside
		  return 0;		  
		if ((dist + v->r) < 0) // Totally inside
		  view.planes.isInside |= 1u << i;
*/
	  }
	}
    return mask;
  }

  inline float CullingSafeDistance(unsigned int p, viewParameters* view)
  {
    vertexData* v = &m_vertices[p];
	plane* currPlane = &view->planes.viewplane[0];
	float minDist = v->r + (v->x*currPlane->a + v->y*currPlane->b + v->z*currPlane->c + currPlane->d);
	for (int i = 1; i < 6; i++)
	{
	  currPlane = &view->planes.viewplane[i];
  	  float dist = v->r + (v->x*currPlane->a + v->y*currPlane->b + v->z*currPlane->c + currPlane->d);
      if (dist < minDist)
	    minDist = dist;
	}
    return minDist;
  }

  inline int VertexMorph(unsigned int i, const viewParameters* view, float height_left, float height_right, float &height_morphed)
  {
    /*
    ** Compute the elevation of the morphed vertex.  The return value indicates
    ** whether the vertex is active or not.
    */
    vertexData* v = &m_vertices[i];
    float curr_dist = DISTANCE_SQR2(v, view->position_x, view->position_y, view->position_z);
    float max_dist = SQR(view->invErrorTolerance_max * v->e + v->r);
    if (max_dist > curr_dist)
	{
      float min_dist = SQR(view->invErrorTolerance_min * v->e + v->r);
	  height_morphed = (min_dist > curr_dist) ?
		                v->height :
	                   ((max_dist - curr_dist) * v->height + (curr_dist - min_dist) * 0.5f * (height_left + height_right)) / (max_dist - min_dist);
	  v->y = height_morphed;
      return 1; // True (TOTALLY ACTIVE)
    }
    else
      return 0; // False (NOT ACTIVE)
  }

protected:
  void CleanUp();
  int BuildData(const float origin_x, const float origin_y, const float origin_z, 
			    const float scale_x , const float scale_y , const float scale_z,
				float* heightmap, int width, int height);

  int BuildData(TerrainImpl::vertexData* vertices, int width, int height, int lineOffset);

  void VertexLodCompute(
    unsigned int  i,      /* column index */
    unsigned int  j,      /* row index */
    int           di,     /* non-negative col offset to bisected edge endpoint */
    int           dj,     /* row offset to bisected edge endpoint */
    unsigned int  n       /* one less array width/height (zero for leaves) */
  );

  static void subDataReindex(
    TerrainImpl::vertexData        *vvo,   // rearranged data
    const TerrainImpl::vertexData  *vvi,   // linearly indexed data
    unsigned int      level,  // refinement level
    unsigned int      p,      // DAG parent and triangle apex (quadtree index)
    unsigned int      c,      // DAG child (quadtree index)
    unsigned int      i,      // triangle apex (linear index)
    unsigned int      j,      // base vertex #1 (linear index)
    unsigned int      k       // base vertex #2 (linear index)
  );

  //Rnd*              m_renderer;
  vertexData*       m_vertices;
  unsigned int      m_levels;
  unsigned int      m_size;
  char              m_errorMsg[300];
  unsigned int      m_indexing;
  PROGRESS_CALLBACK m_progressCallback;
  void*             m_progressCallbackData;

  float        m_bbox_min_x, m_bbox_min_y, m_bbox_min_z;
  float        m_bbox_max_x, m_bbox_max_y, m_bbox_max_z;
};

#endif
