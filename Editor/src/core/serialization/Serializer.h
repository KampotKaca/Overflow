#ifndef SERIALIZER_H
#define SERIALIZER_H

#include <yaml-cpp/yaml.h>
#include "core/utils.h"

namespace overflow
{
    class Serializer
    {
    public:
        explicit Serializer(std::filesystem::path filePath)
            : m_SavePath(std::move(filePath)), m_Doc(){ m_Doc << YAML::BeginMap; }
        ~Serializer() = default;

        void PushClass(const std::string &name)
        { m_Doc << YAML::Key << name << YAML::BeginMap; }
        void PopClass() { m_Doc << YAML::EndMap; }

		void PushArrayClass() { m_Doc << YAML::BeginMap; }

        void PushArray(const std::string &name)
        { m_Doc << YAML::Key << name << YAML::Value << YAML::BeginSeq; }
        void PopArray() { m_Doc << YAML::EndSeq; }

        void Push(const std::string &name, const std::string& var);
        void Push(const std::string &name, bool var);

        void Push(const std::string &name, int32_t var);
        void Push(const std::string &name, uint32_t var);
        void Push(const std::string &name, int64_t var);
        void Push(const std::string &name, uint64_t var);
        void Push(const std::string &name, float_t var);
        void Push(const std::string &name, double_t var);

        void Push(const std::string &name, const vec2& var);
        void Push(const std::string &name, const vec2i& var);
        void Push(const std::string &name, const vec3& var);
        void Push(const std::string &name, const vec3i& var);
        void Push(const std::string &name, const vec4& var);
        void Push(const std::string &name, const vec4i& var);

        void Save()
        {
            m_Doc << YAML::EndMap;

            if (!std::filesystem::exists(m_SavePath.parent_path()))
                std::filesystem::create_directory(m_SavePath.parent_path());
            std::ofstream stream(m_SavePath);
            stream << m_Doc.c_str();

			YAML::Node node;
        }

    private:
        std::filesystem::path m_SavePath;
        YAML::Emitter m_Doc;
    };
}


#endif //SERIALIZER_H
