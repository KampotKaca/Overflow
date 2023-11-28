#version 460 core

//16 bits for instance
//8  bits for texture
//4  bits for uvX
//4  bits for uvY
layout(location = 0) in uint aID;

//layout(std140, binding=3) uniform Camera_UBO
//{
//    mat4 c_View_Projection;
//};

//const uint c_Max_BufferSize = 256;
//uniform mat4 u_Model[c_Max_BufferSize];

out uvec4 vOut;

void main(void)
{
    uint instanceID = aID >> 16u;                               //first 16bits
    uint texID = (aID << 16u) >> 24u;                           //next 8bits
    uvec2 uv = uvec2((aID << 24u) >> 28u, (aID << 28u) >> 28u); //last 4 and 4 bits

//    gl_Position = c_View_Projection * u_Model[instanceID] * vec4(vec2(uv.x - 0.5f, uv.y - 0.5f), 0, 1.0);
    gl_Position = vec4(vec2(uv.x - 0.5f, uv.y - 0.5f), 0, 1.0f);
    vOut = uvec4(instanceID, texID, uv);
}