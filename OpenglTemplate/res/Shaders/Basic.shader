#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 texcoord;
uniform mat4 MVP;
uniform vec4 color;
out vec4 colorV;
out vec2 v_texcoord;
void main()
{
	gl_Position =MVP * vec4(position, 1);
	colorV = color;
	v_texcoord = texcoord;
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;
in vec2 v_texcoord;
in vec4 colorV;
uniform sampler2D u_texture;
void main()
{
	color = texture (u_texture, v_texcoord);
	 
}