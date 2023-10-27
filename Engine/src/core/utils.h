#ifndef UTILS_H
#define UTILS_H

#include "math.h"
#include "log.h"
#include "uuid.h"
#include "core.h"
#include "time.h"

namespace overflow::utils
{
	enum class DebugLogLevel
	{
		None = 0, HighAssert = 1, High = 2,
		Medium = 3, Low = 4, Notification = 5
	};

	static DebugLogLevel s_DebugLogLevel = DebugLogLevel::High;

	void SetGLDebugLogLevel(DebugLogLevel level);
	void EnableGLDebugging();

	bool i_case_compare(const std::string_view& str1, const std::string_view& str2);
	std::_String_view_iterator<std::char_traits<char>> i_case_contains
			(const std::string_view& haystack, const std::string_view& needle);

	bool get_named_file(const std::filesystem::path& folder,
	                    const std::string& fileName, std::string& fName);
}

namespace overflow
{
	template<typename T>
	using scope = std::unique_ptr<T>;

	template<typename T>
	using ref = std::shared_ptr<T>;

#define over_cast(x, y) std::dynamic_pointer_cast<x>(y)
#define make_ref(x, ...) std::make_shared<x>(__VA_ARGS__)
#define make_scope(x, ...) std::make_unique<x>(__VA_ARGS__)

#define INSTANCE(x) \
        static EditorWindowManager& Instance()\
		{\
			static EditorWindowManager s_Instance;\
			return s_Instance;\
		}
}

#endif //UTILS_H