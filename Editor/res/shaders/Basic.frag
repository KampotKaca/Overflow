#version 460 core

uniform vec4 u_Albedo;
uniform sampler2D u_MainTex;

in vec2 v_UV;

out vec4 FragColor;

void main()
{
    FragColor = texture(u_MainTex, v_UV) * u_Albedo;
}