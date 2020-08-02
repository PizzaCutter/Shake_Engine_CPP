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