#include <imgui.h>
#include "pch.h"
#include "EditorUtils.h"

namespace overflow::edit
{
	//region Operators
	bool operator !=(const ImVec2& v1, const ImVec2& v2) { return v1.x != v2.x || v1.y != v2.y; }
	bool operator ==(const ImVec2& v1, const ImVec2& v2) { return v1.x == v2.x && v1.y == v2.y; }
	
	ImVec2 operator -(const ImVec2& v1, const ImVec2& v2) { return { v1.x - v2.x, v1.y - v2.y }; }
	void operator -=(ImVec2& v1, const ImVec2& v2) { v1.x -= v2.x; v1.y -= v2.y; }
	
	ImVec2 operator +(const ImVec2& v1, const ImVec2& v2) { return { v1.x + v2.x, v1.y + v2.y }; }
	void operator +=(ImVec2& v1, const ImVec2& v2) { v1.x += v2.x; v1.y += v2.y; }
	
	ImVec2 operator *(const ImVec2& v1, float f) { return { v1.x * f, v1.y * f }; }
	void operator *=(ImVec2& v1, float f) { v1.x *= f; v1.y *= f; }
	//endregion
}