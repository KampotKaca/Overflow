#ifndef CORE_H
#define CORE_H

#ifdef PLATFORM_WINDOWS

#else
#error Overflow only supports windows!
#endif //PLATFORM_WINDOWS

#ifdef DEBUG
#define ASSERT(x, ...) if(!(x)) { LOG_ERROR(__VA_ARGS__); __debugbreak(); }
#define CORE_ASSERT(x, ...) if(!(x)) { CORE_ERROR(__VA_ARGS__); __debugbreak(); }
#else
#define ASSERT(x, ...)
#define CORE_ASSERT(x, ...)
#endif //DEBUG

#define BIT(x) (1 << x)
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

#endif //CORE_H
