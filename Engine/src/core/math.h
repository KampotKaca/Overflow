#ifndef MATH_H
#define MATH_H

#include <glm/glm/glm.hpp>
#include <glm/glm/gtc/type_ptr.hpp>
#include <glm/glm/gtx/quaternion.hpp>
#include <glm/glm/gtc/matrix_transform.hpp>
#include <glm/glm/ext/quaternion_float.hpp>
#include <glm/glm/ext/vector_int2.hpp>
#include <glm/glm/ext/vector_int3.hpp>
#include <glm/glm/ext/vector_int4.hpp>
#include <glm/glm/ext/vector_float2.hpp>
#include <glm/glm/ext/vector_float3.hpp>
#include <glm/glm/ext/vector_float4.hpp>
#include <glm/glm/ext/matrix_float4x4.hpp>
#include <glm/glm/ext/matrix_float3x3.hpp>
#include <glm/glm/ext/matrix_float2x2.hpp>
#include <glm/glm/ext/matrix_transform.hpp>
#include <glm/glm/ext/matrix_clip_space.hpp>

namespace overflow
{
	using vec2 = glm::vec2;
	using vec3 = glm::vec3;
	using vec4 = glm::vec4;
	using vec2i = glm::ivec2;
	using vec3i = glm::ivec3;
	using vec4i = glm::ivec4;
	using mat2 = glm::mat2;
	using mat3 = glm::mat3;
	using mat4 = glm::mat4;
	using quat = glm::quat;
}

namespace glm
{
	const float EPSILON = 1e-4f;

	void rotate_matrix(mat4& m4, const vec3& euler);
	void camera_directions(const vec2& angle, vec3& right, vec3& up, vec3& forward);
	int decimal_places(float val);
	float lerp(float a, float b, float t);
	vec3 lerp(const vec3& a, const vec3& b, float t);
}

#endif //MATH_H