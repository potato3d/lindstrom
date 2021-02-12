#include "TerrainImpl.h"

// Standard Libraries
#include <string.h>
#include <stdlib.h>

// Math Library
#include <math.h>
#include <float.h>

// IM Includes
#include "im/im.h"
#include "im/im_image.h"

// Alg
#include "alg/vector.h"

// Some Definitions
#include "Defines.h"

//#include "Rnd.h"

#ifdef _WIN32
  #include <windows.h>
#endif

TerrainImpl::TerrainImpl():m_vertices(0), m_size(0), m_levels(0), /*m_renderer(0),*/ m_indexing(0), m_progressCallback(0), m_progressCallbackData(0)
{}

TerrainImpl::~TerrainImpl()
{
  CleanUp();
}

void TerrainImpl::CleanUp()
{
  if (m_vertices)
  {
    free(m_vertices);
	m_vertices = NULL;
  }
}

int TerrainImpl::LoadFromImage(const char* filename, 
							   const float origin_x, const float origin_y, const float origin_z,
							   const float scale_x,  const float scale_y,  const float scale_z)
{
  int error;

  imFile* ifile = imFileOpen(filename, &error);
  if (error != IM_ERR_NONE)
  {
    switch (error)
	{
	case IM_ERR_OPEN:
	  strcpy(m_errorMsg, "Error while opening the file - read or write.\n");
	  break;

	case IM_ERR_ACCESS:
	  strcpy(m_errorMsg, "Error while accessing the file - read or write.\n");
	  break;

	case IM_ERR_FORMAT:
	  strcpy(m_errorMsg, "Invalid or unrecognized file format.\n");
	  break;

	case IM_ERR_DATA:
	  strcpy(m_errorMsg, "Invalid or unsupported data.\n");
	  break;

	case IM_ERR_COMPRESS:
	  strcpy(m_errorMsg, "Invalid or unsupported compression.\n");
	  break;

	case IM_ERR_MEM:
	  strcpy(m_errorMsg, "Insuficient memory.\n");
	  break;

	case IM_ERR_COUNTER:
	  strcpy(m_errorMsg, "Interrupted by the counter.\n");
	  break;

	default:
	  strcpy(m_errorMsg, "Unknown Error.\n");
	  break;

	}
	return 0;
  }

  if (m_progressCallback)
	m_progressCallback(m_progressCallbackData, 0.0f);

  imImage* image = imFileLoadImage(ifile, 0, &error);

  if (m_progressCallback)
	m_progressCallback(m_progressCallbackData, 0.2f);

  if (error != IM_ERR_NONE)
  {
    switch (error)
	{
	case IM_ERR_OPEN:
	  strcpy(m_errorMsg, "Error while opening the file - read or write.\n");
	  break;

	case IM_ERR_ACCESS:
	  strcpy(m_errorMsg, "Error while accessing the file - read or write.\n");
	  break;

	case IM_ERR_FORMAT:
	  strcpy(m_errorMsg, "Invalid or unrecognized file format.\n");
	  break;

	case IM_ERR_DATA:
	  strcpy(m_errorMsg, "Invalid or unsupported data.\n");
	  break;

	case IM_ERR_COMPRESS:
	  strcpy(m_errorMsg, "Invalid or unsupported compression.\n");
	  break;

	case IM_ERR_MEM:
	  strcpy(m_errorMsg, "Insuficient memory.\n");
	  break;

	case IM_ERR_COUNTER:
	  strcpy(m_errorMsg, "Interrupted by the counter.\n");
	  break;

	default:
	  strcpy(m_errorMsg, "Unknown Error.\n");
	  break;

	}
	return 0;
  }

  float* heightmap = (float*) malloc (image->width*image->height*sizeof(float));
  for (int i = 0; i < image->width*image->height; i++)
  {
    unsigned char* data = (unsigned char*) *image->data;
	heightmap[i] = (float) data[i];
  }
  if (m_progressCallback)
	m_progressCallback(m_progressCallbackData, 0.4f);

  // store data somewhere
  int resp = BuildData(origin_x, origin_y, origin_z, scale_x, scale_y, scale_z, heightmap, image->width, image->height);
  free(heightmap);
  imImageDestroy(image);

  imFileClose(ifile); 

  return resp;
}

int TerrainImpl::BuildData(const float origin_x, const float origin_y, const float origin_z, 
						   const float scale_x , const float scale_y , const float scale_z,
						   float* heightmap, int width, int height)
{
  int levels, n;
  int vertexCount;
  int i, j;

  if ( (width < 1) || (height < 1) )
  {
    strcpy(m_errorMsg, "Invalid Terrain Size.");
    return 0;
  }

  // Calculating number of Levels
  for (levels = 0; (1 << levels) + 1 < MAX(width, height); levels++);
  n = (1 << levels) + 1;
  levels *= 2;

  // There must be at least MIN_LEVEL levels
  if (levels < MIN_LEVEL) {
    strcpy(m_errorMsg, "Heightmap too small.");
    return 0;
  }

  
  // Allocating vertices data
  vertexCount = LN_COUNT(levels);
  if (m_vertices)
    free(m_vertices);
  m_vertices = (TerrainImpl::vertexData*) malloc(sizeof(TerrainImpl::vertexData)*vertexCount);
  if (!m_vertices)
  {
    strcpy(m_errorMsg, "Not Enough Memory to create terrain.");
	return 0;
  }
  
  m_size = COUNT_ONE_DIM(levels);
  m_levels = levels;

  // Filling vertex data
  float min_height = FLT_MAX;
  float max_height = FLT_MIN;
  float progressMax = 0.0f;
  for (i = 0; i < m_size; i++)
  {
	for (j = 0; j < m_size; j++)
    {
      m_vertices[i*m_size + j].e = 0;
	  m_vertices[i*m_size + j].r = 0;

      m_vertices[i*m_size + j].x = origin_x + j*scale_x;
      m_vertices[i*m_size + j].z = origin_z + i*scale_z;

	  // if the vertex is inside original heightmap
	  if ( (i < height) && (j < width) )
	  {
		float height = origin_y + heightmap[i*width + j]*scale_y;
		if (height < min_height)
		  min_height = height;

		if (height > max_height)
		  max_height = height;

		m_vertices[i*m_size + j].y =  m_vertices[i*m_size + j].height = height;
	  }
	  else
	  {
/*/	    // Fills height with origin_y
		m_vertices[i*m_size + j].y = m_vertices[i*m_size + j].height = origin_y + 0;
/*/     // Fills height with last height in corresponding direction
        int i2, j2;
	    if (i >= height)
		  i2 = height-1;
		else
		  i2 = i;

	    if (j >= width)
		  j2 = width-1;
		else
		  j2 = j;
	    m_vertices[i*m_size + j].y = m_vertices[i*m_size + j].height = origin_y + heightmap[i2*width + j2]*scale_y;
//*/
	  }
	}
    if (m_progressCallback)
	{
	  float t = ((float)i / m_size) * 0.6f;
	  if ((t - progressMax) > 0.01f)
	  {
	    progressMax = t;
	    m_progressCallback(m_progressCallbackData, 0.4f + t);
	  }
	}
  }
    
  //filling bounding box data
  m_bbox_min_x = origin_x;
  m_bbox_min_y = min_height;
  m_bbox_min_z = origin_z;
  m_bbox_max_x = origin_x + (m_size-1)*scale_x;
  m_bbox_max_y = max_height;
  m_bbox_max_z = origin_z + (m_size-1)*scale_z;

  m_indexing = LINEAR_INDEXING;

  return 1;
}

int 
TerrainImpl::BuildData(TerrainImpl::vertexData* vertices, int width, int height, int lineOffset)
{
  int levels, n;
  int vertexCount;
  int i, j;

  if ( (width < 1) || (height < 1) )
  {
    strcpy(m_errorMsg, "Invalid Terrain Size.");
    return 0;
  }

  // Calculating number of Levels
  for (levels = 0; (1 << levels) + 1 < MAX(width, height); levels++);
  n = (1 << levels) + 1;
  levels *= 2;

  // There must be at least MIN_LEVEL levels
  if (levels < MIN_LEVEL) {
    strcpy(m_errorMsg, "Heightmap too small.");
    return 0;
  }

  
  // Allocating vertices data
  vertexCount = LN_COUNT(levels);
  if (m_vertices)
    free(m_vertices);
  m_vertices = (TerrainImpl::vertexData*) malloc(sizeof(TerrainImpl::vertexData)*vertexCount);
  if (!m_vertices)
  {
    strcpy(m_errorMsg, "Not Enough Memory to create terrain.");
	return 0;
  }
  
  m_size = COUNT_ONE_DIM(levels);
  m_levels = levels;

  // Filling vertex data
  float min_height = FLT_MAX;
  float max_height = FLT_MIN;
  float progressMax = 0.0f;
  for (i = 0; i < m_size; i++)
  {
	for (j = 0; j < m_size; j++)
    {
      m_vertices[i*m_size + j] = vertices[i*lineOffset + j];
	  float height = vertices[i*lineOffset + j].y;
      if (height < min_height)
	    min_height = height;

	  if (height > max_height)
	    max_height = height;
	}

    if (m_progressCallback)
	{
	  float t = ((float)i / m_size) * 0.6f;
	  if ((t - progressMax) > 0.01f)
	  {
	    progressMax = t;
	    m_progressCallback(m_progressCallbackData, 0.4f + t);
	  }
	}
  }
    
  //filling bounding box data
  m_bbox_min_x = m_vertices[0].x;
  m_bbox_min_y = min_height;
  m_bbox_min_z = m_vertices[0].z;
  m_bbox_max_x = m_vertices[(m_size*m_size)-1].x;
  m_bbox_max_y = max_height;
  m_bbox_max_z = m_vertices[(m_size*m_size)-1].z;

  m_indexing = LINEAR_INDEXING;

  return 1;
}


void
TerrainImpl::VertexLodCompute(
  unsigned int  i,      // column index
  unsigned int  j,      // row index
  int           di,     // non-negative col offset to bisected edge endpoint
  int           dj,     // row offset to bisected edge endpoint 
  unsigned int  n       // one less array width/height (zero for leaves)
)
{
  TerrainImpl::vertexData        * const vp = &m_vertices[j*m_size + i];
  const TerrainImpl::vertexData  *cp;
  float         r;
  unsigned int  k;

  /*
  ** Compute actual error and initialize radius to zero.  The error is
  ** simply the vertical difference between the vertex and the bisected
  ** edge, i.e. the error between two consecutive levels of refinement.
  ** This object-space error can be replaced with any measure of error,
  ** as long as the nesting step below is performed.
  */

  vp->e = fabsf(vp->y - 0.5f * (m_vertices[(j-dj)*m_size + (i-di)].y + m_vertices[(j+dj)*m_size + (i+di)].y));
  vp->r = 0.0f;

  /*
  ** If the vertex is not a leaf node, ensure that the error and radius are
  ** nested using information from its four children.  Note that the offsets
  ** (+di, +dj) and (-di, -dj) from (i, j) initially get us to the two
  ** vertices of the bisected edge.  By "rotating" (di, dj) 45 degrees (in
  ** a topological sense), we arrive at one of the children of (i, j)
  ** (assuming we're not on a boundary).  Successive 90-degree rotations
  ** then allow us to visit all four children.
  */

  if (n) {
    /*
    ** di' = (di - dj) / 2
    ** dj' = (di + dj) / 2
    */
    dj = (di + dj) / 2;
    di -= dj;
    k = 4;
    do {
      /*
      ** Test whether child vertex exists.
      */
      if ((i != 0 || di >= 0) && (i != n || di <= 0) &&
          (j != 0 || dj >= 0) && (j != n || dj <= 0)) {
        /*
        ** Inflate error and radius as needed.
        */
	    cp = &m_vertices[(j + dj)*m_size + (i + di)];
        vp->e = MAX(vp->e, cp->e);
        r = DISTANCE(vp, cp) + cp->r;
        vp->r = MAX(vp->r, r);
      }
      /*
      ** di' = -dj
      ** dj' = +di
      */
      dj += di;
      di -= dj;
      dj += di;
    } while (--k);
  }
}

int TerrainImpl::PreProcess()
{
  if (!m_vertices)
  {
    strcpy(m_errorMsg, "Terrain Vertices Pointer is NULL.");
    return 0;
  }

  int       n = m_size-1;
  unsigned int i, j, s;
  int       a, b, c;

  /*
  ** Compute error and radius bottom-up, level-by-level.  This is done
  ** assuming a standard 2D matrix layout of the data, since this layout
  ** allows easy access to all four children of a vertex.  Depending on
  ** the choice of indexing scheme, the data may later have to be rearranged.
  */

  if (m_progressCallback)
    m_progressCallback(m_progressCallbackData, 0.0f);
  float progressMax = 0.0;
  for (a = c = 1, b = 2, s = 0; (unsigned int)a != n; a = c = b, b *= 2, s = n) {
    /*
    ** Process level in black quadtree.
    */
    for (j = a; j < n; j += b) {
      for (i = 0; i <= n; i += b) {
		VertexLodCompute(i, j, 0, a, s);
		VertexLodCompute(j, i, a, 0, s);
      }
    }
    /*
    ** Process level in white quadtree.
    */
    for (j = a; j < n; c = -c, j += b)
      for (i = a; i < n; c = -c, i += b)
		VertexLodCompute(i, j, a, c, n);

	// Calling Progress Callback
    if (m_progressCallback)
	{
	  float t = ( (log10f((float)a)/log10f(2.0f)) / ((float)m_levels/2.0f));
	  if ((t - progressMax) > 0.01f)
	  {
	    progressMax = t;
	    m_progressCallback(m_progressCallbackData, t);
	  }
	}
  }

  /*
  ** Lock center and corner vertices.
  */
  m_vertices[0].e = m_vertices[n].e = m_vertices[(n+1)*n].e = m_vertices[n*(n+1)].e = m_vertices[n/2*(n+1) + n/2].e = FLT_MAX;
  m_vertices[0].r = m_vertices[n].r = m_vertices[(n+1)*n].r = m_vertices[n*(n+1)].r = m_vertices[n/2*(n+1) + n/2].r = FLT_MAX;

  return 1;
}

unsigned int
TerrainImpl::DataReindex()
{
  unsigned      vertexCount = 0;

  if (m_indexing == LINEAR_INDEXING)
  {
	TerrainImpl::vertexData* vp;
    const unsigned        l = m_levels / 2, n = 1 << l, m = n / 2;
    unsigned              i;

  /*
  ** Rearrange data to interleaved quadtree layout.  This is done by
  ** traversing the 2D linear array and the quadtree array in parallel in
  ** recursive refinement order, since this is the only (simple) way we
  ** know how to map quadtree array indices to actual vertex locations.
  ** First visit entire quadtree array to ensure that ghost vertices
  ** (holes) are initialized.
  */
    vertexData nullVertex = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

    vertexCount = IQ_COUNT(m_levels);
    vp = (TerrainImpl::vertexData*) malloc(sizeof(TerrainImpl::vertexData)*vertexCount);
    if (!vp)
    {
      strcpy(m_errorMsg, "Not Enough Memory to create terrain.");
	  return 0;
    }
    for (i = 0; i != vertexCount; i++)
	  vp[i] = nullVertex;

    if (m_progressCallback)
	  m_progressCallback(m_progressCallbackData, 0.0f);
    //-------------------------------------------------------
	subDataReindex(
      vp, m_vertices, m_levels, IQ_ROOT_S(l),
      LN_INDEX(m, m, l), LN_INDEX(0, 0, l), LN_INDEX(n, 0, l)
    );
    //-------------------------------------------------------

	if (m_progressCallback)
	  m_progressCallback(m_progressCallbackData, 0.25f);

    //-------------------------------------------------------
	subDataReindex(
      vp, m_vertices, m_levels, IQ_ROOT_E(l),
      LN_INDEX(m, m, l), LN_INDEX(n, 0, l), LN_INDEX(n, n, l)
    );
    //-------------------------------------------------------

	if (m_progressCallback)
	  m_progressCallback(m_progressCallbackData, 0.5f);

    //-------------------------------------------------------
	subDataReindex(
      vp, m_vertices, m_levels, IQ_ROOT_N(l),
      LN_INDEX(m, m, l), LN_INDEX(n, n, l), LN_INDEX(0, n, l)
    );
    //-------------------------------------------------------

	if (m_progressCallback)
	  m_progressCallback(m_progressCallbackData, 0.75f);

	//-------------------------------------------------------
    subDataReindex(
      vp, m_vertices, m_levels, IQ_ROOT_W(l),
      LN_INDEX(m, m, l), LN_INDEX(0, n, l), LN_INDEX(0, 0, l)
    );
    //-------------------------------------------------------
	if (m_progressCallback)
	  m_progressCallback(m_progressCallbackData, 1.0f);

  /*
  ** Copy corners.
  */

    vp[IQ_I_SW(l)] = m_vertices[0*m_size + 0];
    vp[IQ_I_SE(l)] = m_vertices[0*m_size + n];
    vp[IQ_I_NE(l)] = m_vertices[n*m_size + n];
    vp[IQ_I_NW(l)] = m_vertices[n*m_size + 0];

    free(m_vertices);
    m_vertices = vp;
	m_indexing = INTERLEAVED_QUADTREE_INDEXING;

    return vertexCount;
  }
  return 0;
}

void
TerrainImpl::subDataReindex(
  TerrainImpl::vertexData        *vvo,   // rearranged data
  const TerrainImpl::vertexData  *vvi,   // linearly indexed data
  unsigned int      level,  // refinement level
  unsigned int      p,      // DAG parent and triangle apex (quadtree index)
  unsigned int      c,      // DAG child (quadtree index)
  unsigned int      i,      // triangle apex (linear index)
  unsigned int      j,      // base vertex #1 (linear index)
  unsigned int      k       // base vertex #2 (linear index)
)
{
  if (level) 
  {
    // Copy corresponding vertex from linear layout to quadtree layout.
    vvo[p] = vvi[i];
    subDataReindex(vvo, vvi, level - 1, IQ_CHILD_LEFT(p, c), LN_CHILD_LEFT(i, j, k));
    subDataReindex(vvo, vvi, level - 1, IQ_CHILD_RIGHT(p, c), LN_CHILD_RIGHT(i, j, k));
  }
}

//void TerrainImpl::Render(viewParameters view, Rnd* renderer = NULL)
//{
//  Rnd* currRenderer = renderer;
//  if (!currRenderer)
//    currRenderer = m_renderer;
//
//  if (currRenderer)
//  {
//	currRenderer->PreRender(this);
//	currRenderer->Render(this, &view);
//	currRenderer->PosRender(this);
//  }
//}

void TerrainImpl::GetBBox(float *x_min, float *y_min, float *z_min,
                          float *x_max, float *y_max, float *z_max) const
{
  if (x_min)
    *x_min = m_bbox_min_x;
  if (y_min)
    *y_min = m_bbox_min_y;
  if (z_min)
    *z_min = m_bbox_min_z;
  if (x_max)
    *x_max = m_bbox_max_x;
  if (y_max)
    *y_max = m_bbox_max_y;
  if (z_max)
    *z_max = m_bbox_max_z;
}

bool TerrainImpl::GetHeight(float x, float z, float* height)
{
  if (x < m_bbox_min_x || x > m_bbox_max_x ||
	  z < m_bbox_min_z || z > m_bbox_max_z )
    return false;

  float terrain_size_x = m_bbox_max_x - m_bbox_min_x;
  float terrain_size_z = m_bbox_max_z - m_bbox_min_z;

  float index_x = ( (x - m_bbox_min_x) / terrain_size_x ) * (m_size-1);
  float index_z = ( (z - m_bbox_min_x) / terrain_size_z ) * (m_size-1);

  int index_x_1 = (int) floor(index_x);
  int index_x_2 = index_x_1+1;
  if (index_x_2 > m_size-1)
  {
    index_x_2 = index_x_1;
	index_x_1 = index_x_2-1;
  }

  int index_z_1 = (int) floor(index_z);
  int index_z_2 = index_z_1+1;
  if (index_z_2 > m_size-1)
  {
    index_z_2 = index_z_1;
	index_z_1 = index_z_2-1;
  }

  float t = m_vertices[index_z_1*m_size + index_x_1].height * (1-(index_x - index_x_1)) * (1-(index_z - index_z_1)) +
	        m_vertices[index_z_2*m_size + index_x_1].height * (1-(index_x - index_x_1)) * (1-(index_z_2 - index_z)) +
			m_vertices[index_z_2*m_size + index_x_2].height * (1-(index_x_2 - index_x)) * (1-(index_z_2 - index_z)) +
			m_vertices[index_z_1*m_size + index_x_2].height * (1-(index_x_2 - index_x)) * (1-(index_z - index_z_1));

  if (height)
    *height = t;

  return true;
}

void TerrainImpl::SetProgressCallback(PROGRESS_CALLBACK cb, void* data)
{
  m_progressCallback = cb;
  m_progressCallbackData = data;
}

//*************************************************************************************
// VTF I/O
//*************************************************************************************
typedef struct
{
  unsigned int magic_number;
  unsigned int version;
  unsigned int levels;
  unsigned int size;
  unsigned int count;
  unsigned int indexing;
  float bbmin_x, bbmin_y, bbmin_z;
  float bbmax_x, bbmax_y, bbmax_z;
} VTF_Header;

#define VTF_MAGIC_NUMBER     ( ('v' << 30) | ('t' << 20) | ( 'f' << 10) )
#define VTF_VERSION          1

int TerrainImpl::Load(const char* filename, bool outOfCore)
{
  CleanUp();
  if (!filename)
  {
    strcpy(m_errorMsg, "Filename is NULL.");
    return 0;
  }

  FILE* fp = fopen(filename, "rb");
  if (!fp)
  {
    strcpy(m_errorMsg, "File doesn't exist.");
    return 0;
  }
  
  VTF_Header header;
  if (fread(&header, sizeof(VTF_Header), 1, fp) != 1)
  {
//    sprintf(m_errorMsg, "Could not read '%s'\n%s.", filename, strerror(errno));
    return 0;
  }

  if (header.magic_number != VTF_MAGIC_NUMBER)
  {
    strcpy(m_errorMsg, "This is not a VTF file.");
	return 0;
  }

  if (header.version > VTF_VERSION)
  {
    strcpy(m_errorMsg, "Version newer than this program can handle.");
	return 0;
  }
  if (outOfCore)
  {
    fclose(fp);
#ifdef _WIN32
	HANDLE file = CreateFile(filename,
	                         GENERIC_READ,
							 FILE_SHARE_READ,
							 NULL,
							 OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL | FILE_FLAG_RANDOM_ACCESS,
							 NULL);

    if (!file)
    {
      sprintf(m_errorMsg, "Could not open '%s'.", filename);
      return 0;
    }

	HANDLE mapping = CreateFileMapping(file,
		                               NULL,
									   PAGE_READONLY,
									   0,
									   0,
									   NULL);
	if (!mapping)
	{
      strcpy(m_errorMsg, "CreateFileMapping() failed.");
      CloseHandle(file);
      return NULL;
    }

	void* data =  MapViewOfFile(mapping,
		                        FILE_MAP_READ,
							    0,
							    0,
							    0);
    if (!data)
	{
      strcpy(m_errorMsg, "MapViewOfFile() failed\n");
      CloseHandle(mapping);
      CloseHandle(file);
      return NULL;
    }
	data = (void*) ((char*) data + sizeof(VTF_Header));
	m_vertices = (TerrainImpl::vertexData*) data;
#else
//#error Not Implemented Yet.
#endif
  }
  else
  {
	m_vertices = (TerrainImpl::vertexData*) malloc (header.count * sizeof(TerrainImpl::vertexData));
    if (!m_vertices)
	{
      fprintf(stderr, "malloc() failed: %s\n");
      fclose(fp);
      return 0;
	}
    if (fread(m_vertices, sizeof(TerrainImpl::vertexData), header.count, fp) != header.count)
	{
//      sprintf(m_errorMsg, "Could not read '%s'\n%s.", filename, strerror(errno));
      free(m_vertices);
	  m_vertices = NULL;
      fclose(fp);
      return NULL;
	}
	fclose(fp);
  }

  m_levels = header.levels;
  m_size = header.size;
  m_indexing = header.indexing;

  m_bbox_min_x = header.bbmin_x; m_bbox_min_y = header.bbmin_y; m_bbox_min_z = header.bbmin_z;
  m_bbox_max_x = header.bbmax_x; m_bbox_max_y = header.bbmax_y; m_bbox_max_z = header.bbmax_z;
  return 1;
}

int TerrainImpl::Save(const char* filename)
{
  if (!filename)
  {
    strcpy(m_errorMsg, "Filename is NULL.");
    return 0;
  }

  FILE* fp = fopen(filename, "wb");
  if (!fp)
  {
//    sprintf(m_errorMsg, "Could not create '%s'.\n%s.", filename, strerror(errno));
    return 0;
  }

  VTF_Header header;
  header.magic_number = VTF_MAGIC_NUMBER;
  header.version = VTF_VERSION;
  header.size = m_size;
  header.levels = m_levels;
  header.indexing = m_indexing;
  if (m_indexing == LINEAR_INDEXING)
    header.count = LN_COUNT(m_levels);
  else
    header.count = IQ_COUNT(m_levels);
  header.bbmin_x = m_bbox_min_x; header.bbmin_y = m_bbox_min_y; header.bbmin_z = m_bbox_min_z;
  header.bbmax_x = m_bbox_max_x; header.bbmax_y = m_bbox_max_y; header.bbmax_z = m_bbox_max_z;

  if (fwrite(&header, sizeof(VTF_Header), 1, fp) != 1 ||
	  fwrite(m_vertices, sizeof(TerrainImpl::vertexData), header.count, fp) != header.count)
  {
//    sprintf(m_errorMsg, "Could not write data to '%s'.\n%s.", filename, strerror(errno));
    fclose(fp);
    return 0;
  }
  fclose(fp);

  return 1;
}
