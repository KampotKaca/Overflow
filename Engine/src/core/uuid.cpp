#include "pch.h"
#include "uuid.h"

namespace overflow
{
    std::random_device UUID::s_Device;
    std::mt19937_64 UUID::s_Engine(s_Device());
    std::uniform_int_distribution<uint64_t> UUID::s_Distribution;
}