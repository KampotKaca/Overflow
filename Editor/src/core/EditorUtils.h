#ifndef EDITOR_UTILS_H
#define EDITOR_UTILS_H

#include "overflow.h"

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
	//region Definitions
	static const ImVec4 VECTOR_STYLES[] =
			{
					{ 0.8f, 0.1f, 0.15f, 1.0f }, { 0.9f, 0.2f, 0.2f, 1.0f }, { 0.8f, 0.1f, 0.15f, 1.0f },
					{ 0.2f, 0.7f, 0.2f, 1.0f  }, { 0.3f, 0.8f, 0.3f, 1.0f }, { 0.2f, 0.7f, 0.2f, 1.0f },
					{ 0.1f, 0.25f, 0.8f, 1.0f }, { 0.2f, 0.35f, 0.9f, 1.0f}, { 0.1f, 0.25f, 0.8f, 1.0f },
					{ 0.5f, 0.43f, 0.7f, 1.0f }, { 0.6f, 0.53f, 0.8f, 1.0f}, { 0.5f, 0.43f, 0.7f, 1.0f },
			};

	static const ImGuiDataTypeInfo GDataTypeInfo[] =
			{
					{ sizeof(char),             "S8",   "%d",   "%d"    },
					{ sizeof(unsigned char),    "U8",   "%u",   "%u"    },
					{ sizeof(short),            "S16",  "%d",   "%d"    },
					{ sizeof(unsigned short),   "U16",  "%u",   "%u"    },
					{ sizeof(int),              "S32",  "%d",   "%d"    },
					{ sizeof(unsigned int),     "U32",  "%u",   "%u"    },
#ifdef _MSC_VER
					{ sizeof(ImS64),            "S64",  "%I64d","%I64d" },
					{ sizeof(ImU64),            "U64",  "%I64u","%I64u" },
#else
					{ sizeof(ImS64),            "S64",  "%lld", "%lld"  },
        { sizeof(ImU64),            "U64",  "%llu", "%llu"  },
#endif
					{ sizeof(float),            "float", "%.3f","%f"    },
					{ sizeof(double),           "double","%f",  "%lf"   },
			};
	static const std::string VECTOR_NAMES[] = { "X", "Y", "Z", "W" };
	static const std::string VECTOR_IDS[] = { "##X", "##Y", "##Z", "##W" };
	static const std::string VECTOR_COLUMN_IDS[] = { "##col_vX", "##col_vY", "##col_vZ", "##col_vW" };
	//endregion
	//region Basics
	bool DrawScalar(const char* label, ImGuiDataType data_type, void* v);
	bool DrawString(const char* label, std::string& v);
	bool DrawStringBox(const char* label, std::string& v);

	bool DrawNumber(const char* label, int16_t& v);
	bool DrawNumber(const char* label, uint16_t& v);
	bool DrawNumber(const char* label, int32_t& v);
	bool DrawNumber(const char* label, uint32_t& v);
	bool DrawNumber(const char* label, int64_t & v);
	bool DrawNumber(const char* label, uint64_t & v);
	bool DrawNumber(const char* label, float_t& v);
	bool DrawNumber(const char* label, double_t& v);
	//endregion
	//region Colored_Vectors
	bool DrawNoNameScalar(const char* label, ImGuiDataType data_type, void* v, float speed);

	bool DrawVectorN(const char* label, ImGuiDataType data_type, int size, void* vec, void* resetValue);

	bool DrawVector(const char* label, vec2& vec, float_t resetValue = 0.0f);
	bool DrawVector(const char* label, vec3& vec, float_t resetValue = 0.0f);
	bool DrawVector(const char* label, vec4& vec, float_t resetValue = 0.0f);

	bool DrawVector(const char* label, vec2i& vec, int32_t resetValue = 0.0f);
	bool DrawVector(const char* label, vec3i& vec, int32_t resetValue = 0.0f);
	bool DrawVector(const char* label, vec4i& vec, int32_t resetValue = 0.0f);
	//endregion
}

#endif //EDITOR_UTILS_H
