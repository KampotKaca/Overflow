#ifndef EDITOR_UTILS_H
#define EDITOR_UTILS_H

namespace overflow::edit
{
	//region Operators
	bool operator !=(const ImVec2& v1, const ImVec2& v2);
	bool operator ==(const ImVec2& v1, const ImVec2& v2);
	
	ImVec2 operator -(const ImVec2& v1, const ImVec2& v2);
	void operator -=(ImVec2& v1, const ImVec2& v2);
	
	ImVec2 operator +(const ImVec2& v1, const ImVec2& v2);
	void operator +=(ImVec2& v1, const ImVec2& v2);
	
	ImVec2 operator *(const ImVec2& v1, float f);
	void operator *=(ImVec2& v1, float f);
	//endregion
}

#endif //EDITOR_UTILS_H
