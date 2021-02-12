/*************************************************************
* Simple Geometry Shader for testing heightmap texture
**************************************************************/

#version 120
#extension GL_EXT_geometry_shader4 : enable
#extension GL_EXT_gpu_shader4 : enable

// Number of nodes in recursion tree
uniform int nodeCount;

// Heighmap texture
uniform sampler2D lodTexSampler;
uniform float invLodTexWidth;
uniform float invLodTexHeight;

void computeVertex( int i )
{
	// Get vertex position
	vec4 vertex = gl_PositionIn[i];
	
	// Compute texel coords
	vec2 texelCoord;
	texelCoord.x = vertex.x * invLodTexWidth;
	texelCoord.y = vertex.y * invLodTexHeight;
	
	// Get vertex height
	vertex.z = texture2D( lodTexSampler, texelCoord, 0 ).r;
	
	// Output vertex position
	gl_Position = gl_ModelViewProjectionMatrix * vertex;
	
	// Output color
	gl_FrontColor = gl_FrontColorIn[i];
}

// void main()
// {
// 	int i = 0;
// 	while( i < gl_VerticesIn )
// 	{  
// 		// Vertex 0
// 		computeVertex( i );
// 		EmitVertex();
//     
// 		// Vertex 1
// 		computeVertex( i + 1 );
// 		EmitVertex();
//     
//     	// Vertex 2
//     	computeVertex( i + 2 );
// 		EmitVertex();
//     
// 	    // Finished triangle
// 	    EndPrimitive();
// 	    
// 	    i += 3;
//   }
// } 

void main(void)
{
	for( float i = 0.0f; i < 43.0f; ++i )
	{
		gl_Position = gl_ModelViewProjectionMatrix * vec4( 0.0f, 0.0f, 0.0f + i, 1.0f );
		gl_FrontColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
 		EmitVertex();
 		
 		gl_Position = gl_ModelViewProjectionMatrix * vec4( 10.0f, 0.0f, 0.0f + i, 1.0f );
		gl_FrontColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
 		EmitVertex();
 		
 		gl_Position = gl_ModelViewProjectionMatrix * vec4( 10.0f, 10.0f, 0.0f + i, 1.0f );
		gl_FrontColor = vec4( 1.0f, 1.0f, 1.0f, 1.0f );
 		EmitVertex();
 		
 		EndPrimitive();		
	}
}