#ifndef PCH_H
#define PCH_H

#if PLATFORM_WINDOWS
#include <Windows.h>
#undef min
#undef max
#endif

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <filesystem>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <random>
#include <limits>
#include <thread>
#include <memory>
#include <sys/stat.h>
#include <cctype>
#include <iostream>
#include <functional>
#include <utility>

#endif //PCH_H
