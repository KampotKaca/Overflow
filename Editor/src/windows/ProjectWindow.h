#ifndef PROJECT_WINDOW_H
#define PROJECT_WINDOW_H

#include "EditorWindow.h"

namespace overflow::edit
{
	class ProjectWindow : public EditorWindow
	{
	public:
		ProjectWindow() = default;
		~ProjectWindow() override = default;

		const char *Name() override { return "Project"; }
		void Awake() override;

	protected:
		void Draw() override;
	};
}

#endif //PROJECT_WINDOW_H