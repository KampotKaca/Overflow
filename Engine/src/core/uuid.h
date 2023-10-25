#ifndef UUID_H
#define UUID_H

namespace overflow
{
    struct UUID
    {
    public:
        UUID() : m_UUID(s_Distribution(s_Engine)){}
        explicit UUID(uint64_t uuid) : m_UUID(uuid){}

        operator uint64_t() const { return m_UUID; }
    private:
        uint64_t m_UUID;

        static std::random_device s_Device;
        static std::mt19937_64 s_Engine;
        static std::uniform_int_distribution<uint64_t> s_Distribution;
    };
}

namespace std
{
    template<>
    struct hash<overflow::UUID>
    {
        std::size_t operator()(const overflow::UUID& uuid)
        {
            return hash<uint64_t>()((uint64_t)uuid);
        }
    };
}

#endif //UUID_H