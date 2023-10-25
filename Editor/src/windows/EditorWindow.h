#ifndef EDITOR_WINDOW_H
#define EDITOR_WINDOW_H

#include <imgui.h>
#include "overflow.h"

namespace overflow::edit
{
	class EditorWindow
	{
	public:
		virtual ~EditorWindow() = default;
		[[nodiscard]] bool IsOpen()const { return p_IsOpen; }
		void Open(bool open) { p_IsOpen = open; }

		virtual const char* Name() = 0;

	protected:
		virtual void Draw() = 0;
		virtual void Awake() = 0;

		bool p_IsOpen = true;

	private:

		friend class EditorWindowManager;
	};
}

#endif //EDITOR_WINDOW_H
