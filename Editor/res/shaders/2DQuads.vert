#version 460 core

//12 bits for instance
//4  bits for vertex
//8  bits for texture
//4  bits for uvX
//4  bits for uvY
layout(location = 0) in uint aID;

layout(std140, binding=3) uniform Camera_UBO
{
    mat4 c_View_Projection;
};

const uint c_Max_BufferSize = 256;
uniform mat4 u_Model[c_Max_BufferSize];

out uvec4 vOut;

void main(void)
{
    uint instanceID = aID & 0xFFFu;                             //first 12bits
    uint vertexID = (aID >> 12u) & 0xFu;                        //next 4bits
    uint texID = (aID >> 16u) & 0xFFu;                          //next 8bits
    ivec2 uv = ivec2((aID >> 24u) & 0xFu, (aID >> 28u) & 0xFu); //last 4 and 4 bits

    uint x = vertexID / 2,
         y = vertexID % 2;

    gl_Position = c_View_Projection * u_Model[instanceID] * vec4(vec2(x * 0.5f, y * 0.5f), 0, 1.0);
    vOut = uvec4(instanceID, texID, uv);
}