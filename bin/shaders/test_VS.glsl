// only with geometry shader support
#version 120
//#version 110

void main(void)
{
	gl_Position = gl_Vertex;//ftransform();
	gl_FrontColor = gl_Color;
}
