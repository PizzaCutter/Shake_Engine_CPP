#type vertex
#version 330 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec4 a_color;
layout(location=2) in vec2 a_texcoord;

uniform mat4 u_viewProjection;

out vec3 out_position;
out vec4 out_color;
out vec2 out_texcoord;

void main()
{
	out_position = a_position;
	out_color = a_color;
	out_texcoord = a_texcoord;

    gl_Position = u_viewProjection * vec4(a_position, 1.0); 
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 out_position;
in vec4 out_color;
in vec2 out_texcoord;

uniform vec2 u_tilingSize;
uniform sampler2D u_sampler;

void main()
{
	//color = texture(u_sampler, out_texcoord * u_tilingSize);
	color = out_color;
} 


