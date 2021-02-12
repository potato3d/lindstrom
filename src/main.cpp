/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield 
 *
 * This application is open source and may be redistributed and/or modified   
 * freely and without restriction, both in commericial and non commericial applications,
 * as long as this copyright notice is maintained.
 * 
 * This application is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/
#include <gl/glew.h>

#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osgProducer/Viewer>
#include <osg/CoordinateSystemNode>
#include <osg/Image>

#include <tecUtil/Hud.h>

#include <queue>
#include <sstream>
#include <cassert>

#include "TerrainImpl.h"

#define USE_GEOMETRY_SHADER

struct Triangle 
{
	osg::Vec3 i;
	osg::Vec3 j;
	osg::Vec3 k;
};

struct Texel
{
	float r; // height
	float g; // error
	float b; // radius
	float a;
};

class LindstromDrawable : public osg::Drawable
{
public:
	META_Object( test, LindstromDrawable )

    enum ShaderMode
    {
        NONE,
        SIMPLE_GEOMETRY,
        FIRST_ALG,
        SECOND_ALG
    };

	LindstromDrawable()
	{
	}

	~LindstromDrawable()
	{
		for( int s = 0; s < _texWidth; ++s )
		{
			delete [] _heightmap[s];
		}

		delete [] _heightmap;
	}

	LindstromDrawable( osg::Image* heightImg )
		: _initialized( false ), _minHeight( FLT_MAX ), _maxHeight( FLT_MIN ), _errorThreshold( 1.0f ), _programObject( 0 ),
          _shaderMode( NONE ), _glHeightTextureId( 0 ), _glStTextureId( 0 ), _glPathTextureId( 0 )
	{
		assert( heightImg != NULL );
		setUseDisplayList( false );

		_texWidth = heightImg->s();
		_texHeight = heightImg->t();

		// log in base 2
		// levels begin with zero, so if maxLeves == 16 there are 17 levels on total
		_maxLevels = 2.0f * logf( _texWidth - 1 ) * 1.4426950408889634073599246810023;

		// Equivalent to number of nodes in recursion tree
		// TODO: testing with only one triangle, so nodeCount /= 4
		//_nodeCount = (_texWidth-1) * (_texWidth-1) * 4;
		//_nodeCount *= 0.25f;

		// TODO: testing geometry shader: must limit triangle size to 16x16 = 256 < ( 1024 / 3 )
		_nodeCount = (17-1) * (17-1) * 4;
		_nodeCount *= 0.25f;

		// Terrain loader and preprocessor from Gustavo
		_terrainLoader.LoadFromImage( heightImg->getFileName().c_str(), 0, 0, 0, 1, 0.1, 1 );
		_terrainLoader.PreProcess();

		_heightmap = new Texel*[_texWidth];
		for( int s = 0; s < _texWidth; ++s )
		{
			_heightmap[s] = new Texel[_texHeight];
			for( int t = 0; t < _texHeight; ++t )
			{
				Texel& lodTexel = _heightmap[s][t];
				lodTexel.r = _terrainLoader.GetVertexHeight( s + t*_texWidth );
				lodTexel.g = _terrainLoader.GetVertexError( s + t*_texWidth );
				lodTexel.b = _terrainLoader.GetVertexRadius( s + t*_texWidth );

				if( lodTexel.r < _minHeight )
					_minHeight = lodTexel.r;
				else if( lodTexel.r > _maxHeight )
					_maxHeight = lodTexel.r;
			}
		}

		Triangle t;
		int middle = _texWidth*0.5f;

		// SOUTH_TRIANGLE
		//t.i.set( middle, middle, _heightmap[middle][middle].r );
		//t.j.set( 0, 0, _heightmap[0][0].r );
		//t.k.set( _texWidth-1, 0, _heightmap[_texWidth-1][0].r );

		// TODO: testing geometry shader: must limit triangle size to 16x16 = 256 < ( 1024 / 3 )
		t.i.set( 8.0f, 8.0f, _heightmap[8][8].r );
		t.j.set( 0, 0, _heightmap[0][0].r );
		t.k.set( 16.0f, 0, _heightmap[16][0].r );

		createTextures( t );
		//createTextures2( t );
	}

	/** Copy constructor using CopyOp to manage deep vs shallow copy.*/
	LindstromDrawable( const LindstromDrawable& object,const osg::CopyOp& copyop=osg::CopyOp::SHALLOW_COPY )
		: osg::Drawable( object, copyop )
	{
	}

	void increaseErrorThreshold()
	{
		_errorThreshold += 0.1f;
	}

	void decreaseErrorThreshold()
	{
		_errorThreshold -= 0.1f;
		if( _errorThreshold < 0.1f )
			_errorThreshold = 0.1f;
	}

	float errorThreshold()
	{
		return _errorThreshold;
	}

    void reloadShaders( ShaderMode mode )
    {
        _shaderMode = mode;
        _initialized = false;
    }

	unsigned int nextPowerOf2( unsigned int value )
	{
		value |= ( value >> 1 );
		value |= ( value >> 2 );
		value |= ( value >> 4 );
		value |= ( value >> 8 );
		value |= ( value >> 16 );
		return ( value + 1 );
	}

    void init()
    {
        glewInit();
        std::cout << std::endl << std::endl << "***************************" << std::endl;

        /************************************************************************/
        /* Setup shaders                                                        */
        /************************************************************************/

        _programObject = glCreateProgramObjectARB();

        // Geometry Shader require a Vertex Shader to be used
        initShader( _programObject, "shaders/test_VS.glsl", GL_VERTEX_SHADER_ARB );
        // Fragment Shader for per-fragment lighting
        initShader( _programObject, "shaders/test_FS.glsl", GL_FRAGMENT_SHADER_ARB );

#ifdef USE_GEOMETRY_SHADER

        // Get max number of geometry shader output vertices
        GLint outputVertexLimit;
        glGetIntegerv( GL_MAX_GEOMETRY_OUTPUT_VERTICES_EXT, &outputVertexLimit );
        std::cout << "Max GS output vertices: " << outputVertexLimit << "\n";

		GLint outputComponentLimit;  
		glGetIntegerv( GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS_EXT, &outputComponentLimit ); 
		std::cout << "Max GS output components: " << outputComponentLimit << "\n";

        std::string gsFilename;
        GLint outputVertexCount;

        switch( _shaderMode )
        {
        case SIMPLE_GEOMETRY:
            gsFilename = "shaders/test_GS.glsl";
            //outputVertexCount = 3;
			// TODO: testing
			outputVertexCount = outputVertexLimit;
			break;
        case FIRST_ALG:
            gsFilename = "shaders/test1_GS.glsl";
            outputVertexCount = _nodeCount*3;
            break;
        case NONE:
        default:
            _programObject = 0;
            _initialized = true;
            return;
        }
        
        // Geometry Shader loading
        initShader( _programObject, gsFilename.c_str(), GL_GEOMETRY_SHADER_EXT );

        ////Setup Geometry Shader////

        // one of: GL_POINTS, GL_LINES, GL_LINES_ADJACENCY_EXT, GL_TRIANGLES, GL_TRIANGLES_ADJACENCY_EXT
        //Set GL_TRIANGLES primitives as INPUT
        glProgramParameteriEXT( _programObject,GL_GEOMETRY_INPUT_TYPE_EXT , GL_TRIANGLES );

        // one of: GL_POINTS, GL_LINE_STRIP, GL_TRIANGLE_STRIP  
        //Set TRIANGLE STRIP as OUTPUT
        glProgramParameteriEXT( _programObject,GL_GEOMETRY_OUTPUT_TYPE_EXT , GL_TRIANGLE_STRIP );

        // This parameter is very important and have an important impact on Shader performances
        // Its value must be chosen closer as possible to real maximum number of vertices
        glProgramParameteriEXT( _programObject,GL_GEOMETRY_VERTICES_OUT_EXT, outputVertexCount );
        std::cout << "GS output set to: " << outputVertexCount << "\n";
#endif

        // Link whole program object (Geometry+Vertex+Fragment)
        glLinkProgramARB( _programObject );

        // Test link success
        GLint ok = false;
        glGetObjectParameterivARB( _programObject, GL_OBJECT_LINK_STATUS_ARB, &ok );
        if( !ok )
        {
            int maxLength=4096;
            char *infoLog = new char[maxLength];
            glGetInfoLogARB(_programObject, maxLength, &maxLength, infoLog);
            std::cout<<"Link error: "<<infoLog<<"\n";
            delete []infoLog;
        }

        // Program validation
        glValidateProgramARB(_programObject);
        ok = false;
        glGetObjectParameterivARB(_programObject, GL_OBJECT_VALIDATE_STATUS_ARB, &ok);
        if (!ok)
        {
            int maxLength=4096;
            char *infoLog = new char[maxLength];
            glGetInfoLogARB(_programObject, maxLength, &maxLength, infoLog);
            std::cout<<"Validation error: "<<infoLog<<"\n";
            delete []infoLog;
        }

        // Bind program object for parameters setting
        glUseProgramObjectARB(_programObject);

        // Send parameters to shaders

        /************************************************************************/
        /* Setup textures                                                       */
        /************************************************************************/

        // Heightmap with error and radius

        // TODO: don't copy data, should have only one array allocated
        _glTexHeight = new float[_texWidth*_texHeight*3];

        unsigned int dst = 0;

        for( int t = 0; t < _texHeight; ++t )
        {
            for( int s = 0; s < _texWidth; ++s )
            {
                Texel& lodTexel = _heightmap[s][t];
                _glTexHeight[dst] = lodTexel.r; // height
                ++dst;
                _glTexHeight[dst] = lodTexel.g; // error
                ++dst;
                _glTexHeight[dst] = lodTexel.b; // radius
                ++dst;
            }
        }

        glActiveTextureARB( GL_TEXTURE0_ARB );
        glGenTextures( 1, &_glHeightTextureId );
        glBindTexture( GL_TEXTURE_2D, _glHeightTextureId );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGB32F_ARB, _texWidth, _texHeight, 0, GL_RGB, GL_FLOAT, _glTexHeight );

        // Geometry shader parameters
        // TODO: should we really pass w - 1 and h - 1?
        glUniform1iARB(glGetUniformLocationARB(_programObject, "lodTexSampler"), 0 );
        glUniform1fARB(glGetUniformLocationARB(_programObject, "invLodTexWidth"), 1.0f / ( _texWidth - 1.0f ) );
        glUniform1fARB(glGetUniformLocationARB(_programObject, "invLodTexHeight"), 1.0f / ( _texHeight - 1.0f ) );

        // The following textures have the same size: _nodeCount
        // Also used as break condition in triangle generation
        glUniform1fARB(glGetUniformLocationARB(_programObject, "nodeCount"), (float)_nodeCount );

        GLint maxTexSize;
        glGetIntegerv( GL_MAX_TEXTURE_SIZE, &maxTexSize );

		float width;
		float height;
		if( _nodeCount < maxTexSize )
		{
			width = nextPowerOf2( _nodeCount - 1 );
			height = 1;
		}
		else
		{
			width = maxTexSize;
			height = (int)ceil( (float)_nodeCount / (float)maxTexSize );
			height = nextPowerOf2( height - 1 );
		}

		float* tex = new float[width*height*4];

		for( int from = 0, to = 0, limit = width*height*4; to < limit; to+=4 )
		{
			if( from < _nodeCount )
			{
				Texel& t = _stTexture[from++];
				tex[to] = t.r;
				tex[to+1] = t.g;
				tex[to+2] = t.b;
				tex[to+3] = t.a;
			}
			else
			{
				tex[to] = 0.0f;
				tex[to+1] = 0.0f;
				tex[to+2] = 0.0f;
				tex[to+3] = 0.0f;
			}
		}

        glUniform1fARB(glGetUniformLocationARB(_programObject, "texWidth"), width );
		glUniform1fARB(glGetUniformLocationARB(_programObject, "invTexWidth"), 1.0f/(float)width );

        // ST texture
        glActiveTextureARB( GL_TEXTURE1_ARB );
        glGenTextures( 1, &_glStTextureId );
        glBindTexture( GL_TEXTURE_2D, _glStTextureId );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, width, height, 0, GL_RGBA, GL_FLOAT, tex );

        glUniform1iARB(glGetUniformLocationARB(_programObject, "stTexSampler"), 1 );

		for( int from = 0, to = 0, limit = width*height*4; to < limit; to+=4 )
		{
			if( from < _nodeCount )
			{
				Texel& t = _pathTexture[from++];
				tex[to] = t.r;
				tex[to+1] = t.g;
				tex[to+2] = t.b;
				tex[to+3] = t.a;
			}
			else
			{
				tex[to] = 0.0f;
				tex[to+1] = 0.0f;
				tex[to+2] = 0.0f;
				tex[to+3] = 0.0f;
			}
		}

        // Path texture
        glActiveTextureARB( GL_TEXTURE2_ARB );
        glGenTextures( 1, &_glPathTextureId );
        glBindTexture( GL_TEXTURE_2D, _glPathTextureId );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F_ARB, width, height, 0, GL_RGBA, GL_FLOAT, tex );

        glUniform1iARB( glGetUniformLocationARB(_programObject, "pathTexSampler"), 2 );

        // Finish
		delete [] tex;
		_initialized = true;
    }

    void initShader( GLhandleARB _programObject, const char *filen, GLuint type )
    {
        //Source file reading
        std::string buff;
        std::ifstream file;
        std::string filename=filen;
        std::cerr.flush();
        file.open(filename.c_str());
        std::string line;
        while(std::getline(file, line))
            buff += line + "\n";

        const GLcharARB *txt=buff.c_str();

        //Shader object creation
        GLhandleARB object = glCreateShaderObjectARB(type);

        //Source code assignment
        glShaderSourceARB(object, 1, &txt, NULL);

        //Compile shader object
        glCompileShaderARB(object);

        //Check if shader compiled
        GLint ok = 0;
        glGetObjectParameterivARB(object, GL_OBJECT_COMPILE_STATUS_ARB, &ok);
        if (!ok)
        {
            int maxLength=4096;
            char *infoLog = new char[maxLength];
            glGetInfoLogARB(object, maxLength, &maxLength, infoLog);
            std::cout<<"Compilation error: "<<infoLog<<"\n";
            delete []infoLog;
        }

        // attach shader to program object
        glAttachObjectARB(_programObject, object);

        // delete object, no longer needed
        glDeleteObjectARB(object);

        //Global error checking
        std::cout<<"InitShader: "<<filen<<" Errors: "<<gluErrorString(glGetError())<<"\n";
    }

	virtual void drawImplementation( osg::State& state ) const
	{
		//glBegin( GL_POINTS );
		//for( int s = 0; s < _texWidth; ++s )
		//{
		//	for( int t = 0; t < _texHeight; ++t )
		//	{
		//		glVertex3f( s, t, _heightmap[s][t].r );
		//	}
		//}
		//glEnd();

		LindstromDrawable* me = const_cast<LindstromDrawable*>( this );
		me->_trianglesRendered = 0;

        if( _initialized )
        {
            if( _shaderMode != NONE )
            {
                glUseProgramObjectARB( _programObject );
                glActiveTextureARB( GL_TEXTURE0_ARB );
                glBindTexture( GL_TEXTURE_2D, _glHeightTextureId );
                glActiveTextureARB( GL_TEXTURE1_ARB );
                glBindTexture( GL_TEXTURE_2D, _glStTextureId );
                glActiveTextureARB( GL_TEXTURE2_ARB );
                glBindTexture( GL_TEXTURE_2D, _glPathTextureId );
            }
        }
        else
        {
            me->init();
        }

		// Get and store psi = viewport height / ( fovy * user threshold )
		double fovy;
		double aspect;
		double zNear;
		double zFar;
		state.getProjectionMatrix().getPerspective( fovy, aspect, zNear, zFar );
		me->_errorPsi = state.getCurrentViewport()->height() / ( osg::DegreesToRadians( fovy ) * _errorThreshold );

        // Send error psi to Geometry Shader
        if( _shaderMode != NONE )
            glUniform1fARB(glGetUniformLocationARB(_programObject, "errorPsi"), me->_errorPsi );

		// Get current viewpoint
		state.getModelViewMatrix().getLookAt( me->_viewpoint, osg::Vec3(), osg::Vec3() );

		if( _shaderMode != NONE )
			glUniform4fARB(glGetUniformLocationARB(_programObject, "viewpoint"), me->_viewpoint[0], me->_viewpoint[1],
			                                                                     me->_viewpoint[2], 1.0f );

		glBegin( GL_TRIANGLES );

        if( ( _shaderMode == NONE ) || ( _shaderMode == SIMPLE_GEOMETRY ) )
        {
            //me->meshRefine();
            me->refine( 0 );
            //me->refine2( 0 );
        }
        else if( _shaderMode == FIRST_ALG )
        {
            int middle = _texWidth*0.5f;

            // SOUTH_TRIANGLE
            //osg::Vec3f i( middle, middle, _heightmap[middle][middle].r );
            //osg::Vec3f j( 0, 0, _heightmap[0][0].r );
            //osg::Vec3f k( _texWidth-1, 0, _heightmap[_texWidth-1][0].r );

			// TODO: testing geometry shader: must limit triangle size to 16x16 = 256 < ( 1024 / 3 )
			glVertex3f( 8.0f, 8.0f, _heightmap[8][8].r );
			glVertex3f( 0, 0, _heightmap[0][0].r );
			glVertex3f( 16.0f, 0, _heightmap[16][0].r );
        }
		
		glEnd();

        // Reset state
        if( _shaderMode != NONE )
        {
            glUseProgramObjectARB( 0 );
            glActiveTextureARB( GL_TEXTURE0_ARB );
            glBindTexture( GL_TEXTURE_2D, 0 );
            // TODO: prevents hud/fps from working
            //glActiveTextureARB( GL_TEXTURE1_ARB );
            //glBindTexture( GL_TEXTURE_2D, 0 );
            //glActiveTextureARB( GL_TEXTURE2_ARB );
            //glBindTexture( GL_TEXTURE_2D, 0 );
        }
	}

    unsigned int trianglesRendered()
    {
        return _trianglesRendered;
    }

	virtual osg::BoundingBox computeBound() const
	{
		float heightLimit;
		if( osg::absolute( _minHeight ) > osg::absolute( _maxHeight ) )
			heightLimit = osg::absolute( _minHeight );
		else
			heightLimit = osg::absolute( _maxHeight );

		return osg::BoundingBox( 0, 0, -heightLimit, _texWidth, _texHeight, heightLimit );
	}

	void createTextures( const Triangle& t )
	{
		// Create one or more topology textures
		_stTexture = new Texel[_nodeCount];
		_pathTexture = new Texel[_nodeCount];

		std::queue<Triangle> toVisit;
		Triangle tri;
		Triangle child;
		int id = 0;
		int forward;
		int back;

		toVisit.push( t );

		while( !toVisit.empty() && ( id < _nodeCount ) )
		{
			tri = toVisit.front();
			toVisit.pop();

			Texel& stTexel = _stTexture[id];
			stTexel.r = tri.i.x();
			stTexel.g = tri.i.y();
			stTexel.b = tri.j.x();
			stTexel.a = tri.j.y();

			computeForwardBack( forward, back, id );

			Texel& pathTexel = _pathTexture[id];
			pathTexel.r = forward;
			pathTexel.g = back;

			leftChild( child, tri );
			toVisit.push( child );
			rightChild( child, tri );
			toVisit.push( child );

			++id;
		}
	}

	void createTextures2( const Triangle& t )
	{
		// Create one or more topology textures
		_stTexture = new Texel[_nodeCount];
		_pathTexture = new Texel[_nodeCount];
		int id = 0;

		createTexturesRecursive( t, id, _maxLevels );
	}

	void createTexturesRecursive( const Triangle& t, int& id, int level )
	{
		if( id >= _nodeCount )
			return;
		else if( level <= 0 )
			return;

		int myId = id;

		Texel& stTexel = _stTexture[id++];
		stTexel.r = t.i.x();
		stTexel.g = t.i.y();
		stTexel.b = t.j.x();
		stTexel.a = t.j.y();

		Triangle child;
		leftChild( child, t );
		createTexturesRecursive( child, id, level - 1 );
		rightChild( child, t );
		createTexturesRecursive( child, id, level - 1 );

		Texel& pathTexel = _pathTexture[myId];
		pathTexel.g = id;
	}

	void leftChild( Triangle& out, const Triangle& in ) const
	{
		// i = ( j + k ) / 2
		// j = i
		// k = j
		out.i.x() = ( in.j.x() + in.k.x() ) * 0.5f;
		out.i.y() = ( in.j.y() + in.k.y() ) * 0.5f;
		out.i.z() = _heightmap[(int)out.i.x()][(int)out.i.y()].r;
		out.j = in.i;
		out.k = in.j;
	}

	void rightChild( Triangle& out, const Triangle& in ) const
	{
		// i = ( j + k ) / 2
		// j = k
		// k = i
		out.i.x() = ( in.j.x() + in.k.x() ) * 0.5f;
		out.i.y() = ( in.j.y() + in.k.y() ) * 0.5f;
		out.i.z() = _heightmap[(int)out.i.x()][(int)out.i.y()].r;
		out.j = in.k;
		out.k = in.i;
	}

	void computeBack( int& back, int id )
	{
		if( id == 0 )
			back = _nodeCount;
		else if( ( id % 2 ) == 1 )
			back = id + 1;
		else
			computeBack( back, ( id - 1 ) / 2 );
	}

	void computeForwardBack( int& forward, int& back, int id )
	{
		forward = 2*id + 1;

		computeBack( back, id );

		/*if( ( id % 2 ) == 1 )
			back = id + 1;
		else
			back = id / 2;*/

		if( forward >= _nodeCount )
			forward = back;
	}

	void computeTriangleVertexes( Triangle& t, const Texel& texel )
	{
		t.i.x() = texel.r;
		t.i.y() = texel.g;
		t.i.z() = _heightmap[(int)t.i.x()][(int)t.i.y()].r;

		t.j.x() = texel.b;
		t.j.y() = texel.a;
		t.j.z() = _heightmap[(int)t.j.x()][(int)t.j.y()].r;

		// Counter clockwise rotation of j around i
		// s'' = s + t - t'
		// t'' = t + s' - s
		t.k.x() = texel.r + texel.g - texel.a;
		t.k.y() = texel.g + texel.b - texel.r;
		t.k.z() = _heightmap[(int)t.k.x()][(int)t.k.y()].r;
	}

	bool isActive( osg::Vec3& splitVertex )
	{
		// Get lod data from split vertex s,t
		Texel& lodTexel = _heightmap[(int)splitVertex.x()][(int)splitVertex.y()];
		splitVertex.z() = lodTexel.r;
		return osg::square( _errorPsi*lodTexel.g + lodTexel.b ) > ( _viewpoint - splitVertex ).length2();
	}

	void refine( int id )
	{
		Triangle t;

		while( id < _nodeCount )
		{
			// Get triangle vertex data from id
			// R = s
			// G = t
			// B = s'
			// A = t'
			Texel& stTexel = _stTexture[id];

			// Get recursive path information from id
			Texel& pathTexel = _pathTexture[id];

			// Values needed for split vertex computation
			t.j.x() = stTexel.b; // s'
			t.j.y() = stTexel.a; // t'

			// Counter clockwise rotation of j around i
			// s'' = s + t - t'
			// t'' = t + s' - s
			t.k.x() = stTexel.r + stTexel.g - stTexel.a; // s''
			t.k.y() = stTexel.g + stTexel.b - stTexel.r; // t''

			// Compute split vertex's coordinates
			// s = ( s' + s'' ) / 2
			// t = ( t' + t'' ) / 2
			osg::Vec3 splitVertex( ( t.j.x() + t.k.x() ) * 0.5f,
								   ( t.j.y() + t.k.y() ) * 0.5f,
								   0.0f );

			// Check if split vertex needs refinement
			if( isActive( splitVertex) && ( pathTexel.r != pathTexel.g ) )
			{
				// Step forward
				id = pathTexel.r;
			}
			else
			{
				// Need remaining triangle data
				// Vertex i
				t.i.x() = stTexel.r;
				t.i.y() = stTexel.g;
				t.i.z() = _heightmap[(int)t.i.x()][(int)t.i.y()].r;
				// Vertex j
				t.j.z() = _heightmap[(int)t.j.x()][(int)t.j.y()].r;
				// Vertex k
				t.k.z() = _heightmap[(int)t.k.x()][(int)t.k.y()].r;

				// Emit triangle
				glVertex3fv( t.i.ptr() );
				glVertex3fv( t.j.ptr() );
				glVertex3fv( t.k.ptr() );
				++_trianglesRendered;

				// Step back
				id = pathTexel.g;
			}
		}
	}

	void refine2( int id )
	{
		Triangle t;

		while( id < _nodeCount )
		{
			// Get triangle vertex data from id
			// R = s
			// G = t
			// B = s'
			// A = t'
			Texel& stTexel = _stTexture[id];

			// Get recursive path information from id
			Texel& pathTexel = _pathTexture[id];

			// Values needed for split vertex computation
			t.j.x() = stTexel.b; // s'
			t.j.y() = stTexel.a; // t'

			t.k.x() = stTexel.r + stTexel.g - stTexel.a; // s''
			t.k.y() = stTexel.g + stTexel.b - stTexel.r; // t''

			// Compute split vertex's coordinates
			// s = ( s' + s'' ) / 2
			// t = ( t' + t'' ) / 2
			osg::Vec3 splitVertex( ( t.j.x() + t.k.x() ) * 0.5f,
								   ( t.j.y() + t.k.y() ) * 0.5f,
								   0.0f );

			if( isActive( splitVertex ) &&  ( pathTexel.g != ( id + 1 ) ) )
			{
				// Step forward
				++id;
			}
			else
			{
				// Need remaining triangle data
				// Vertex i
				t.i.x() = stTexel.r;
				t.i.y() = stTexel.g;
				t.i.z() = _heightmap[(int)t.i.x()][(int)t.i.y()].r;
				// Vertex j
				t.j.z() = _heightmap[(int)t.j.x()][(int)t.j.y()].r;
				// Vertex k
				t.k.z() = _heightmap[(int)t.k.x()][(int)t.k.y()].r;

				// Emit triangle
				glVertex3fv( t.i.ptr() );
				glVertex3fv( t.j.ptr() );
				glVertex3fv( t.k.ptr() );
				++_trianglesRendered;

				// Step back
				id = pathTexel.g;
			}
		}
	}

	void subMeshRefine( const Triangle& t, int level )
	{
		osg::Vec3 splitVertex( ( t.j.x() + t.k.x() ) * 0.5f,
							   ( t.j.y() + t.k.y() ) * 0.5f,
							   0.0f );

		if( ( level > 0 ) && isActive( splitVertex ) )
		{
			Triangle child;
			leftChild( child, t );
			subMeshRefine( child, level-1 );
			rightChild( child, t );
			subMeshRefine( child, level-1 );
		}
		else
		{
			glVertex3fv( t.i.ptr() );
			glVertex3fv( t.j.ptr() );
			glVertex3fv( t.k.ptr() );
			++_trianglesRendered;
		}
	}

	void meshRefine()
	{
		Triangle t;
		int middle = _texWidth*0.5f;

		// SOUTH_TRIANGLE
		t.i.set( middle, middle, _heightmap[middle][middle].r );
		t.j.set( 0, 0, _heightmap[0][0].r );
		t.k.set( _texWidth-1, 0, _heightmap[_texWidth-1][0].r );
		subMeshRefine( t, _maxLevels - 1 );

		// TODO: comparing with new algorithm
		return;

		// EAST_TRIANGLE
		t.j = t.k;
		t.k.set( _texWidth-1, _texHeight-1, _heightmap[_texWidth-1][_texHeight-1].r );
		subMeshRefine( t, _maxLevels - 1 );

		// NORTH_TRIANGLE
		t.j = t.k;
		t.k.set( 0, _texHeight-1, _heightmap[0][_texHeight-1].r );
		subMeshRefine( t, _maxLevels - 1 );

		// WEST_TRIANGLE
		t.j = t.k;
		t.k.set( 0, 0, _heightmap[0][0].r );
		subMeshRefine( t, _maxLevels - 1 );
	}

private:
    bool _initialized;
	int _texWidth;
	int _texHeight;
	float _minHeight;
	float _maxHeight;
	int _maxLevels;
	int _nodeCount;

	int _trianglesRendered;

	float _errorPsi;
	float _errorThreshold;
	osg::Vec3 _viewpoint;


    // Shader program
    GLhandleARB _programObject;
    ShaderMode _shaderMode;

    // Height texture
    Texel** _heightmap;
    unsigned int _glHeightTextureId;
    float* _glTexHeight;

    // ST texture
    unsigned int _glStTextureId;
    Texel* _stTexture;

    // Path texture
    unsigned int _glPathTextureId;
	Texel* _pathTexture;

    // Terrain loader
	TerrainImpl _terrainLoader;
};

class ErrorThresholdHandler : public osgGA::GUIEventHandler
{
public:
	ErrorThresholdHandler( LindstromDrawable* drawable, tecUtil::Hud* report )
	{
		_drawable = drawable;
		_report = report;
	}

	virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
	{
		switch( ea.getEventType() )
		{
        case( osgGA::GUIEventAdapter::FRAME ):
            {
                std::stringstream ss;
                ss << "Triangle Count: " << _drawable->trianglesRendered();
                _report->setLine( 1, ss.str() );
                return true;
            }

		case( osgGA::GUIEventAdapter::KEYDOWN ):
			if( ea.getKey() == ',' )
			{
				_drawable->decreaseErrorThreshold();
				std::stringstream ss;
				ss << "Error: " << _drawable->errorThreshold();
				_report->setLine( 0, ss.str() );
				return true;
			}
			else if( ea.getKey() == '.' )
			{
				_drawable->increaseErrorThreshold();
				std::stringstream ss;
				ss << "Error: " << _drawable->errorThreshold();
				_report->setLine( 0, ss.str() );
				return true;
			}
            else if( ea.getKey() == '1' )
            {
                _drawable->reloadShaders( LindstromDrawable::NONE );
                return true;
            }
            else if( ea.getKey() == '2' )
            {
                _drawable->reloadShaders( LindstromDrawable::SIMPLE_GEOMETRY );
                return true;
            }
            else if( ea.getKey() == '3' )
            {
                _drawable->reloadShaders( LindstromDrawable::FIRST_ALG );
                return true;
            }
            else if( ea.getKey() == '4' )
            {
                _drawable->reloadShaders( LindstromDrawable::NONE );
                return true;
            }
		}

		return false;
	}

private:
	LindstromDrawable* _drawable;
	tecUtil::Hud* _report;
};


int main( int argc, char **argv )
{
    // use an ArgumentParser object to manage the program arguments.
    osg::ArgumentParser arguments(&argc,argv);
    
    // set up the usage document, in case we need to print out how to use this program.
    arguments.getApplicationUsage()->setApplicationName(arguments.getApplicationName());
    arguments.getApplicationUsage()->setDescription(arguments.getApplicationName()+" is the standard OpenSceneGraph example which loads and visualises 3d models.");
    arguments.getApplicationUsage()->setCommandLineUsage(arguments.getApplicationName()+" [options] filename ...");
    arguments.getApplicationUsage()->addCommandLineOption("--image <filename>","Load an image and render it on a quad");
    arguments.getApplicationUsage()->addCommandLineOption("--dem <filename>","Load an image/DEM and render it on a HeightField");
    arguments.getApplicationUsage()->addCommandLineOption("-h or --help","Display command line parameters");
    arguments.getApplicationUsage()->addCommandLineOption("--help-env","Display environmental variables available");
    arguments.getApplicationUsage()->addCommandLineOption("--help-keys","Display keyboard & mouse bindings available");

    arguments.getApplicationUsage()->addCommandLineOption("--help-all","Display all command line, env vars and keyboard & mouse bindings.");
    

    // construct the viewer.
    osgProducer::Viewer viewer(arguments);

    // set up the value with sensible default event handlers.
    viewer.setUpViewer(osgProducer::Viewer::STANDARD_SETTINGS);

    // get details on keyboard and mouse bindings used by the viewer.
    viewer.getUsage(*arguments.getApplicationUsage());

    // if user request help write it out to cout.
    bool helpAll = arguments.read("--help-all");
    unsigned int helpType = ((helpAll || arguments.read("-h") || arguments.read("--help"))? osg::ApplicationUsage::COMMAND_LINE_OPTION : 0 ) |
                            ((helpAll ||  arguments.read("--help-env"))? osg::ApplicationUsage::ENVIRONMENTAL_VARIABLE : 0 ) |
                            ((helpAll ||  arguments.read("--help-keys"))? osg::ApplicationUsage::KEYBOARD_MOUSE_BINDING : 0 );
    if (helpType)
    {
        arguments.getApplicationUsage()->write(std::cout, helpType);
        return 1;
    }

    // report any errors if they have occurred when parsing the program arguments.
    if (arguments.errors())
    {
        arguments.writeErrorMessages(std::cout);
        return 1;
    }
    
    osg::Timer_t start_tick = osg::Timer::instance()->tick();

    // read the scene from the list of file specified command line args.
	osg::ref_ptr<osg::Group> loadedModel = new osg::Group();

	osg::ref_ptr<osg::Image> heightmap = osgDB::readImageFile( "heightmap.png" );
	//osg::ref_ptr<osg::Image> heightmap = osgDB::readImageFile( "earth.jpg" );

	osg::Geode* geode = new osg::Geode();
	LindstromDrawable* lindstrom = new LindstromDrawable( heightmap.get() );
	geode->addDrawable( lindstrom );
	loadedModel->addChild( geode );

	tecUtil::Hud* hud = new tecUtil::Hud();
	std::stringstream ss;
	ss << "Error: " << lindstrom->errorThreshold();
	hud->setLine( 0, ss.str() );
	loadedModel->addChild( hud );

    // any option left unread are converted into errors to write out later.
    arguments.reportRemainingOptionsAsUnrecognized();

    // report any errors if they have occurred when parsing the program arguments.
    if (arguments.errors())
    {
        arguments.writeErrorMessages(std::cout);
    }

    osg::Timer_t end_tick = osg::Timer::instance()->tick();

    std::cout << "Time to load = "<<osg::Timer::instance()->delta_s(start_tick,end_tick)<<std::endl;


    // optimize the scene graph, remove redundant nodes and state etc.
    osgUtil::Optimizer optimizer;
    optimizer.optimize(loadedModel.get());

    // pass the loaded scene graph to the viewer.
    viewer.setSceneData(loadedModel.get());

	viewer.getEventHandlerList().push_front( new ErrorThresholdHandler( lindstrom, hud ) );

    // create the windows and run the threads.
    viewer.realize();

    while( !viewer.done() )
    {
        // wait for all cull and draw threads to complete.
        viewer.sync();

        // update the scene by traversing it with the the update visitor which will
        // call all node update callbacks and animations.
        viewer.update();
         
        // fire off the cull and draw traversals of the scene.
        viewer.frame();
        
    }
    
    // wait for all cull and draw threads to complete.
    viewer.sync();

    // run a clean up frame to delete all OpenGL objects.
    viewer.cleanup_frame();

    // wait for all the clean up frame to complete.
    viewer.sync();

    return 0;
}

