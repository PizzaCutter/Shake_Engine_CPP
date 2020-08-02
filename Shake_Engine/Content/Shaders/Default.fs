#version 330 core

layout(location = 0) out vec4 color;

in vec3 out_position;

uniform vec3 u_color;

void main()
{
    color = vec4(u_color, 1.0); 
} 