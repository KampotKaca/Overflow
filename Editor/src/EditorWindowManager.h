#ifndef EDITOR_WINDOW_MANAGER_H
#define EDITOR_WINDOW_MANAGER_H

#include "windows/EditorWindow.h"

namespace overflow::edit
{
	class EditorWindowManager
	{
	public:
		static ref<EditorWindow> GetWindow(const std::string& loc) { return s_Windows[loc]; }
		static void DrawAll();

		template<class T, typename... Args>
		typename std::enable_if<std::is_base_of<EditorWindow, T>::value, ref<T>>::type
		static Create(const std::string& loc, Args&&... args)
		{
			ref<T> window = make_ref(T, std::forward<Args>(args)...);
			s_Windows[loc] = window;
			window->Awake();
			return window;
		}

	private:
		static std::unordered_map<std::string, ref<EditorWindow>> s_Windows;

		friend class Editor;
	};
}

#endif //EDITOR_WINDOW_MANAGER_H
