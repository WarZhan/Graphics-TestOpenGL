#version 140
in vec2 vPosition;
const vec4 white = vec4(1.0, 1.0, 1.0, 1.0);
out vec4 colorOut;

void main()
{
	gl_Position = vec4(vPosition, 0.0, 1.0);
	colorOut = white;
}