/*************************************************************
* Algorithm 1: binary heap node numbering
**************************************************************/

#version 120
#extension GL_EXT_geometry_shader4 : enable
#extension GL_EXT_gpu_shader4 : enable

// Number of nodes in recursion tree
uniform float nodeCount;

// Heighmap texture
uniform sampler2D lodTexSampler;
uniform float invLodTexWidth;
uniform float invLodTexHeight;

// Used for accessing textures below
uniform float texWidth;
uniform float invTexWidth;

// ST texture
uniform sampler2D stTexSampler;
// Path texture
uniform sampler2D pathTexSampler;

// Error psi computed from current camera parameters
uniform float errorPsi;

bool isActive( vec4 splitV )
{
	// Get lod data from split vertex s,t
	vec4 lodTexel = texture2D( lodTexSampler, vec2( splitV.x*invLodTexWidth, splitV.y*invLodTexHeight ) );
	splitV.z = lodTexel.r;
	return ( errorPsi*lodTexel.g + lodTexel.b ) > length( gl_ModelViewMatrixInverse[3] - splitV );
}

void print( float offset, vec4 color )
{
	gl_Position = gl_ModelViewProjectionMatrix * vec4( 0.0f, 0.0f, 0.0f + offset, 1.0f );
	gl_FrontColor = color;
	EmitVertex();
	
	gl_Position = gl_ModelViewProjectionMatrix * vec4( 5.0f, 0.0f, 0.0f + offset, 1.0f );
	gl_FrontColor = color;
	EmitVertex();
	
	gl_Position = gl_ModelViewProjectionMatrix * vec4( 5.0f, 5.0f, 0.0f + offset, 1.0f );
	gl_FrontColor = color;
	EmitVertex();
	
	EndPrimitive();
}

void main()
{
	float id = 0.0f;
  	vec4 vi;
	vec4 vj;
	vec4 vk;
	vec4 stTexel;
	vec4 pathTexel;
	vec4 splitVertex;
	float magic = 0.0f;
	float triangleCount = 0.0f;
	float saveId = 0.0f;
	
  	while( id < nodeCount )
  	//for( int i = 0; i < 2; ++i )
  	{
  		// Get triangle vertex data from id
		// R = s
		// G = t
		// B = s'
		// A = t'
		stTexel = texture2D( stTexSampler, vec2( mod( id, texWidth )*invTexWidth, id*invTexWidth ) );
		
		// Get recursive path information from id
		pathTexel = texture2D( pathTexSampler, vec2( mod( id, texWidth )*invTexWidth, id*invTexWidth ) );

		// Values needed for split vertex computation
		vj.xy = stTexel.ba; // s', t'

		// Counter clockwise rotation of vj around vi
		// s'' = s + t - t'
		// t'' = t + s' - s
		vk.x = stTexel.r + stTexel.g - stTexel.a; // s''
		vk.y = stTexel.g + stTexel.b - stTexel.r; // t''
		
		// Compute split vertex's coordinates
		// s = ( s' + s'' ) / 2
		// t = ( t' + t'' ) / 2
		splitVertex = vec4( ( vj.x + vk.x ) * 0.5f, ( vj.y + vk.y ) * 0.5f, 0.0f, 1.0f );
		
		//++magic;
		
		// Check if split vertex needs refinement
		if( isActive( splitVertex ) && ( pathTexel.r != pathTexel.g ) )
		{
			// Step forward
			id = pathTexel.r;
		}
		else
		{
			// Need remaining triangle data
			// Vertex i
			vi.xy = stTexel.rg; // s, t
			vi.z = texture2D( lodTexSampler, vec2( vi.x * invLodTexWidth, vi.y * invLodTexHeight ) ).r;
			vi.w = 1.0f;
			
			// Vertex j
			vj.z = texture2D( lodTexSampler, vec2( vj.x * invLodTexWidth, vj.y * invLodTexHeight ) ).r;
			vj.w = 1.0f;
			
			// Vertex k
			vk.z = texture2D( lodTexSampler, vec2( vk.x * invLodTexWidth, vk.y * invLodTexHeight ) ).r;
			vk.w = 1.0f;

			// Emit triangle
			gl_Position = gl_ModelViewProjectionMatrix * vi;
			gl_FrontColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
			EmitVertex();
			
			gl_Position = gl_ModelViewProjectionMatrix * vj;
			gl_FrontColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
			EmitVertex();
			
			gl_Position = gl_ModelViewProjectionMatrix * vk;
			gl_FrontColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
			EmitVertex();
			
			// Finished triangle
			EndPrimitive();
			
			// Step back
			id = pathTexel.g;
			
			++triangleCount;
		}
  	} // while
   	
  	//if( triangleCount == 42.0f )
  	{
  		print( 0.0f, vec4( 1.0f, 0.0f, 0.0f, 1.0f ) );
  	}
  	
//   	if( pathTexel.g == 256.0 )
//   	{
//   		print( 1.0f, vec4( 0.0f, 1.0f, 0.0f, 1.0f ) );
//   	}
}
