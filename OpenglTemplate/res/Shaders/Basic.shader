#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
uniform mat4 MVP;
uniform vec4 color;
out vec4 colorV;
void main()
{
	gl_Position =MVP * vec4(position, 1);
	colorV = color;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec4 colorV;
void main()
{
	color = colorV;// vec4(0.5, 0.6, 0.1, 1.0);
}