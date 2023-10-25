#include "pch.h"
#include "Serializer.h"

namespace overflow
{
    void Serializer::Push(const std::string &name, const std::string &var)
    { m_Doc << YAML::Key << name << YAML::Value << var; }

    void Serializer::Push(const std::string &name, bool var)
    { m_Doc << YAML::Key << name << YAML::Value << var; }

    void Serializer::Push(const std::string &name, int32_t var)
    { m_Doc << YAML::Key << name << YAML::Value << var; }

    void Serializer::Push(const std::string &name, uint32_t var)
    { m_Doc << YAML::Key << name << YAML::Value << var; }

    void Serializer::Push(const std::string &name, int64_t var)
    { m_Doc << YAML::Key << name << YAML::Value << var; }

    void Serializer::Push(const std::string &name, uint64_t var)
    { m_Doc << YAML::Key << name << YAML::Value << var; }

    void Serializer::Push(const std::string &name, float_t var)
    { m_Doc << YAML::Key << name << YAML::Value << var; }

    void Serializer::Push(const std::string &name, double_t var)
    { m_Doc << YAML::Key << name << YAML::Value << var; }

    void Serializer::Push(const std::string &name, const vec2 &var)
    {
        m_Doc << YAML::Key << name << YAML::Flow;
        m_Doc << YAML::BeginSeq << var.x << var.y << YAML::EndSeq;
    }

    void Serializer::Push(const std::string &name, const vec3 &var)
    {
        m_Doc << YAML::Key << name << YAML::Flow;
        m_Doc << YAML::BeginSeq << var.x << var.y << var.z << YAML::EndSeq;
    }

    void Serializer::Push(const std::string &name, const vec4 &var)
    {
        m_Doc << YAML::Key << name << YAML::Flow;
        m_Doc << YAML::BeginSeq << var.x << var.y << var.z << var.w << YAML::EndSeq;
    }
}