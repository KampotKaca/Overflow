#include "pch.h"
#include "math.h"

namespace glm
{
	void rotate_matrix(mat4& m4, const vec3& euler)
	{
		vec3 radians = glm::radians(euler);
		m4 = glm::rotate(m4, radians.x, { 1.0f, 0.0f, 0.0f });
		m4 = glm::rotate(m4, radians.y, { 0.0f, 1.0f, 0.0f });
		m4 = glm::rotate(m4, radians.z, { 0.0f, 0.0f, 1.0f });
	}

	void camera_directions(const vec2& angle, vec3& right, vec3& up, vec3& forward)
	{
		vec2 rad = glm::radians(vec2{angle.x + 90.0f, angle.y });

		forward.x = cos(rad.x) * cos(rad.y);
		forward.y = sin(rad.y);
		forward.z = sin(rad.x) * cos(rad.y);
		forward = glm::normalize(forward);

		right = glm::normalize(glm::cross({ 0.0f, 1.0f, 0.0f }, forward));
		up    = glm::normalize(glm::cross(forward, right));
	}

	int decimal_places(float val)
	{
		int decimalPlaces = 0;
		float fractionalPart = std::fabs(val) - std::floor(std::fabs(val));
		while(fractionalPart > EPSILON && decimalPlaces < 4)
		{
			fractionalPart *= 10;
			fractionalPart -= std::floorf(fractionalPart);
			decimalPlaces++;
		}

		return decimalPlaces;
	}

	float lerp(float a, float b, float t) { return a + t * (b - a); }
	vec3 lerp(const vec3& a, const vec3& b, float t) { return a + t * (b - a); }
}