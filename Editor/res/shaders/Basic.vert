#version 460 core
layout(location = 0) in vec3 aPosition;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

layout(std140, binding=3) uniform Camera_UBO
{
    mat4 c_View_Projection;
};

const uint c_Max_InstancingSize = /*insSize*/128;
uniform mat4 u_Model[c_Max_InstancingSize];

out vec2 v_UV;

void main(void)
{
    gl_Position = c_View_Projection * u_Model[gl_InstanceID] * vec4(aPosition, 1.0);
    v_UV = aUV;
}