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

// ST texture
uniform sampler1D stTexSampler;

// Path texture
uniform sampler1D pathTexSampler;

// Error psi computed from current camera parameters
uniform float errorPsi;

struct Triangle
{
	vec4 i;
	vec4 j;
	vec4 k;
};

bool isActive( vec4 splitVertex, vec4 viewpoint )
{
	// Get lod data from split vertex s,t
	vec4 lodTexel = texture2D( lodTexSampler, vec2( splitVertex.x*invLodTexWidth, splitVertex.y*invLodTexWidth ), 0 );
	splitVertex.z = lodTexel.r;
	float error = errorPsi * lodTexel.g + lodTexel.b;
	vec4 toEye = viewpoint - splitVertex;
	return ( error * error ) > dot( toEye, toEye );
}

void main()
{
  	float id = 0;
  	Triangle t;
  	vec4 viewpoint = -gl_ModelViewMatrix[3];
  	
	while( id < nodeCount )
	{
		// Get triangle vertex data from id
		// R = s
		// G = t
		// B = s'
		// A = t'
		vec4 stTexel = texture1D( stTexSampler, id, 0 );

		// Get recursive path information from id
		vec4 pathTexel = texture1D( pathTexSampler, id, 0 );

		// Values needed for split vertex computation
		t.j.x = stTexel.b; // s'
		t.j.y = stTexel.a; // t'

		t.k.x = stTexel.r + stTexel.g - stTexel.a; // s''
		t.k.y = stTexel.g + stTexel.b - stTexel.r; // t''

		// Compute split vertex's coordinates
		// s = ( s' + s'' ) / 2
		// t = ( t' + t'' ) / 2
		vec4 splitVertex = vec4( ( t.j.x + t.k.x ) * 0.5f, ( t.j.y + t.k.y ) * 0.5f, 0.0f, 1.0f );

		// Check if split vertex needs refinement
		if( isActive( viewpoint, splitVertex ) && ( pathTexel.r != pathTexel.g ) )
		{
			// Step forward
			id = pathTexel.r;
		}
		else
		{
			// Need remaining triangle data
			// Vertex i
			t.i.x = stTexel.r;
			t.i.y = stTexel.g;
			t.i.z = texture2D( lodTexSampler, vec2( t.i.x, t.i.y ), 0 ).r;
			// Vertex j
			t.j.z = texture2D( lodTexSampler, vec2( t.j.x, t.j.y ), 0 ).r;
			// Vertex k
			t.k.z = texture2D( lodTexSampler, vec2( t.k.x, t.k.y ), 0 ).r;

			// Emit triangle
			gl_Position = gl_ModelViewProjectionMatrix * t.i;
			gl_FrontColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
			EmitVertex();
			
			gl_Position = gl_ModelViewProjectionMatrix * t.j;
			gl_FrontColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
			EmitVertex();
			
			gl_Position = gl_ModelViewProjectionMatrix * t.k;
			gl_FrontColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
			EmitVertex();
			
			// Finished triangle
			EndPrimitive();
			
			// Step back
			id = pathTexel.g;
		}
	}
} 
