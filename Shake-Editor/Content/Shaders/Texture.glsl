#type vertex
#version 330 core

layout(location=0) in vec3 a_position;
layout(location=1) in vec4 a_color;
layout(location=2) in vec2 a_texcoord;
layout(location=3) in float a_textureslot;
layout(location=4) in vec2 a_tillingSize;

uniform mat4 u_viewProjection;

out vec3 out_position;
out vec4 out_color;
out vec2 out_texcoord;
out float out_textureslot;
out vec2 out_tillingSize;

void main()
{
	out_position = a_position;
	out_color = a_color;
	out_texcoord = a_texcoord;
	out_textureslot = a_textureslot;
	out_tillingSize = a_tillingSize;

    gl_Position = u_viewProjection * vec4(a_position, 1.0); 
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 out_position;
in vec4 out_color;
in vec2 out_texcoord;
in float out_textureslot;
in vec2 out_tillingSize;

uniform vec2 u_tilingSize;
uniform sampler2D[32] u_sampler;

void main()
{
    // TODO[rsmekens]: we might need to use a switch statement since this could be broken for other GPU's
	color = texture(u_sampler[int(out_textureslot)], out_texcoord * out_tillingSize); 
	color *= out_color;
} 


