#ifndef WINDOW_H
#define WINDOW_H

#include "utils.h"

namespace overflow
{
	enum class VSyncMode { None = 0, Full = 1, Half = 2 };
	enum class WindowScaleMode { Windowed = 0, Maximized = 1, FullScreen = 2 };
	enum class OpenGlProfile { Compatibility = 0x00032002, Core = 0x00032001 };

	struct WindowProps
	{
		std::string Title = "WindStorm";
		std::string IconLocations[2] = { "", "" };
		vec2i Version = vec2i(4, 6);
		OpenGlProfile Profile = OpenGlProfile::Core;
		vec2i Size = vec2i(1280, 720);
		WindowScaleMode ScaleMode = WindowScaleMode::Windowed;
		VSyncMode SyncMode = VSyncMode::Full;
		bool DebugOn = true;

		WindowProps();
	};

	class Window
	{
	public:
		virtual ~Window() = default;
		virtual void BeginDraw() = 0;
		virtual void EndDraw() = 0;

		[[nodiscard]] virtual vec2i Size() const = 0;

		virtual void SetVSync(VSyncMode mode) = 0;
		virtual VSyncMode GetVSyncMode() = 0;

		[[nodiscard]] virtual bool ShouldClose() const = 0;
		[[nodiscard]] virtual void* NativePtr()const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
		static void Terminate();
		static void* GetCurrentContext();
		static void MakeContextCurrent(void* window);
	};
}

#endif //WINDOW_H