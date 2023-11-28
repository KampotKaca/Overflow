#version 460 core

//const uint c_Max_BufferSize = 256;
//const uint c_Max_TexureSize = 32;
//uniform sampler2D u_Texture[c_Max_TexureSize];
//uniform vec4 u_Color[c_Max_BufferSize];

flat in uvec4 vOut;
out vec4 FragColor;

void main(void)
{
//    vec4 col = texture(u_Texture[vOut.y], vOut.zw) * u_Color[vOut.x];
    FragColor = vec4(1.0, vOut.zw, 1.0);
}