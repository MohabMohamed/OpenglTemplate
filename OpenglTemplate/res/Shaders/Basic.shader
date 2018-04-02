#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
uniform mat4 MVP;

void main()
{
	gl_Position =MVP * vec4(position, 1);;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
	color = vec4(1.0, 0.0, 0.0, 1.0);
}