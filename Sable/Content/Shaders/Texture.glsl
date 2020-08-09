#type vertex
#version 330 core

layout(location=0) in vec3 a_Position;
layout(location=1) in vec2 a_texcoord;

uniform mat4 u_viewProjection;
uniform mat4 u_Transform;

out vec3 out_position;
out vec2 out_texcoord;

void main()
{
	out_position = a_Position;
	out_texcoord = a_texcoord;
	
    gl_Position = u_viewProjection * u_Transform * vec4(a_Position, 1.0); 
}

#type fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec3 out_position;
in vec2 out_texcoord;

uniform vec3 u_color;
uniform sampler2D u_sampler;

void main()
{
	color = texture(u_sampler, out_texcoord);
    color *= vec4(out_texcoord * u_color.xy, 0.0, 1.0);
} 


