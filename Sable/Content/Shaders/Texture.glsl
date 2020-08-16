#type vertex
#version 330 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec4 a_color;
layout(location=2) in vec2 a_texcoord;
layout(location=3) in float a_textureslot;

uniform mat4 u_viewProjection;

out vec3 out_position;
out vec4 out_color;
out vec2 out_texcoord;
out float out_textureslot;

void main()
{
	out_position = a_position;
	out_color = a_color;
	out_texcoord = a_texcoord;
	out_textureslot = a_textureslot;

    gl_Position = u_viewProjection * vec4(a_position, 1.0); 
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 out_position;
in vec4 out_color;
in vec2 out_texcoord;
in float out_textureslot;

uniform vec2 u_tilingSize;
uniform sampler2D[32] u_sampler;

void main()
{
	color = texture(u_sampler[int(out_textureslot)], out_texcoord); // * u_tillingSize
	color *= out_color;
} 


