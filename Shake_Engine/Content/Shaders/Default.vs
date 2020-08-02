#version 330 core

layout(location=0) in vec3 a_Position;

uniform mat4 u_viewProjection;
uniform mat4 u_Transform;

out vec3 out_position;

void main()
{
	out_position = a_Position;
	
    gl_Position = u_viewProjection * u_Transform * vec4(a_Position, 1.0); 
}