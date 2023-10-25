#include "pch.h"
#include "Deserializer.h"

namespace overflow
{
#define GET_RHS(x)\
    YAML::Node node = m_Doc[m_Doc.size() - 1][name];\
	if(!node)\
	{\
		rhs = def;\
		return false;\
	}\
	rhs = node.as<x>();\
	return true;

    bool Deserializer::GetString(const std::string &name, std::string &rhs, const std::string& def)const { GET_RHS(std::string) }
	bool Deserializer::GetBool  (const std::string &name, bool        &rhs, bool               def)const { GET_RHS(bool)        }
	bool Deserializer::GetInt32 (const std::string &name, int32_t     &rhs, int32_t            def)const { GET_RHS(int32_t)     }
    bool Deserializer::GetInt64 (const std::string &name, int64_t     &rhs, int64_t            def)const { GET_RHS(int64_t)     }
    bool Deserializer::GetUInt32(const std::string &name, uint32_t    &rhs, uint32_t           def)const { GET_RHS(uint32_t)    }
    bool Deserializer::GetUInt64(const std::string &name, uint64_t    &rhs, uint64_t           def)const { GET_RHS(uint64_t)    }
    bool Deserializer::GetFloat (const std::string &name, float_t     &rhs, float_t            def)const { GET_RHS(float_t)     }
    bool Deserializer::GetDouble(const std::string &name, double_t    &rhs, double_t           def)const { GET_RHS(double_t)    }
    bool Deserializer::GetVec2  (const std::string &name, vec2        &rhs, const vec2&        def)const { GET_RHS(vec2)        }
    bool Deserializer::GetVec2I (const std::string &name, vec2i       &rhs, const vec2i&       def)const { GET_RHS(vec2i)       }
    bool Deserializer::GetVec3  (const std::string &name, vec3        &rhs, const vec3&        def)const { GET_RHS(vec3)        }
    bool Deserializer::GetVec3I (const std::string &name, vec3i       &rhs, const vec3i&       def)const { GET_RHS(vec3i)       }
    bool Deserializer::GetVec4  (const std::string &name, vec4        &rhs, const vec4&        def)const { GET_RHS(vec4)        }
    bool Deserializer::GetVec4I (const std::string &name, vec4i       &rhs, const vec4i&       def)const { GET_RHS(vec4i)       }
#undef GET_RHS
}