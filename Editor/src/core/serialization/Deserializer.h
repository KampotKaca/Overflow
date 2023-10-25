#ifndef DESERIALIZER_H
#define DESERIALIZER_H

#include <yaml-cpp/yaml.h>
#include "core/utils.h"

namespace YAML
{
	template<>
	struct convert<overflow::vec2>
	{
		static Node encode(const overflow::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, overflow::vec2& rhs)
		{
			if(!node.IsSequence() || node.size() != 2) return false;
			rhs.x = node[0].as<float_t>();
			rhs.y = node[1].as<float_t>();
			return true;
		}
	};

	template<>
	struct convert<overflow::vec3>
	{
		static Node encode(const overflow::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, overflow::vec3& rhs)
		{
			if(!node.IsSequence() || node.size() != 3) return false;
			rhs.x = node[0].as<float_t>();
			rhs.y = node[1].as<float_t>();
			rhs.z = node[2].as<float_t>();
			return true;
		}
	};

	template<>
	struct convert<overflow::vec4>
	{
		static Node encode(const overflow::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, overflow::vec4& rhs)
		{
			if(!node.IsSequence() || node.size() != 4) return false;
			rhs.x = node[0].as<float_t>();
			rhs.y = node[1].as<float_t>();
			rhs.z = node[2].as<float_t>();
			rhs.w = node[3].as<float_t>();
			return true;
		}
	};

	template<>
	struct convert<overflow::vec2i>
	{
		static Node encode(const overflow::vec2i& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			return node;
		}

		static bool decode(const Node& node, overflow::vec2i& rhs)
		{
			if(!node.IsSequence() || node.size() != 2) return false;
			rhs.x = node[0].as<int32_t>();
			rhs.y = node[1].as<int32_t>();
			return true;
		}
	};

	template<>
	struct convert<overflow::vec3i>
	{
		static Node encode(const overflow::vec3i& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, overflow::vec3i& rhs)
		{
			if(!node.IsSequence() || node.size() != 3) return false;
			rhs.x = node[0].as<int32_t>();
			rhs.y = node[1].as<int32_t>();
			rhs.z = node[2].as<int32_t>();
			return true;
		}
	};

	template<>
	struct convert<overflow::vec4i>
	{
		static Node encode(const overflow::vec4i& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, overflow::vec4i& rhs)
		{
			if(!node.IsSequence() || node.size() != 4) return false;
			rhs.x = node[0].as<int32_t>();
			rhs.y = node[1].as<int32_t>();
			rhs.z = node[2].as<int32_t>();
			rhs.w = node[3].as<int32_t>();
			return true;
		}
	};
}

namespace overflow
{
    class Deserializer
    {
    public:
        explicit Deserializer(const std::filesystem::path& filePath)
        {
            std::ifstream stream(filePath);
            std::stringstream str;
            str << stream.rdbuf();

            m_Doc.push_back(YAML::Load(str.str()));
        }
        ~Deserializer() = default;

        bool PushLayer(const std::string &name)
        {
            YAML::Node node = m_Doc[m_Doc.size() - 1][name];
            if(!node) return false;

            m_Doc.push_back(node);
            return true;
        }

		bool PushArray(const std::string& name)
		{
			YAML::Node node = m_Doc[m_Doc.size() - 1][name];
			if(!node || node.size() == 0) return false;

			m_Doc.push_back(node);
			m_Doc.push_back(node[0]);

			return true;
		}

	    bool PopArray()
	    {
		    m_Doc.pop_back();
		    m_Doc.pop_back();
		    return m_Doc.empty();
	    }

        bool PopLayer()
        {
			m_Doc.pop_back();
            return m_Doc.empty();
        }

		void SetByIndex(size_t index) { m_Doc[m_Doc.size() - 1] = m_Doc[m_Doc.size() - 2][index]; }

        bool GetString(const std::string& name, std::string& rhs, const std::string& def = "") const;
        bool GetBool(const std::string& name, bool& rhs, bool def = false) const;

        bool GetInt32 (const std::string& name, int32_t&  rhs, int32_t  def = 0) const;
        bool GetInt64 (const std::string& name, int64_t&  rhs, int64_t  def = 0) const;
        bool GetUInt32(const std::string& name, uint32_t& rhs, uint32_t def = 0) const;
        bool GetUInt64(const std::string& name, uint64_t& rhs, uint64_t def = 0) const;

        bool GetFloat (const std::string& name, float_t&  rhs, float_t  def = 0) const;
        bool GetDouble(const std::string& name, double_t& rhs, double_t def = 0) const;

        bool GetVec2 (const std::string& name, vec2&  rhs, const vec2&  def = {}) const;
        bool GetVec2I(const std::string& name, vec2i& rhs, const vec2i& def = {}) const;
        bool GetVec3 (const std::string& name, vec3&  rhs, const vec3&  def = {}) const;
        bool GetVec3I(const std::string& name, vec3i& rhs, const vec3i& def = {}) const;
        bool GetVec4 (const std::string& name, vec4&  rhs, const vec4&  def = {}) const;
        bool GetVec4I(const std::string& name, vec4i& rhs, const vec4i& def = {}) const;

		[[nodiscard]] inline size_t size() const { return m_Doc[m_Doc.size() - 2].size(); }


    private:
        std::vector<YAML::Node> m_Doc;
    };
}


#endif //DESERIALIZER_H
