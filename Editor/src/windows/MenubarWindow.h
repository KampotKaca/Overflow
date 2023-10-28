#ifndef MENUBAR_WINDOW_H
#define MENUBAR_WINDOW_H

#include "EditorWindow.h"

namespace overflow::edit
{
	class MenubarWindow : public EditorWindow
	{
	public:
		MenubarWindow();
		~MenubarWindow() override = default;
		
		const char *Name() override { return "##MenuBar"; }
		void Awake() override;
		
	private:
		void Draw() override;
	};
}


#endif //MENUBAR_WINDOW_H
