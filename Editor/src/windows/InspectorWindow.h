#ifndef INSPECTOR_WINDOW_H
#define INSPECTOR_WINDOW_H

#include "EditorWindow.h"

namespace overflow::edit
{
	class InspectorWindow : public EditorWindow
	{
	public:
		InspectorWindow() = default;
		~InspectorWindow() override = default;

		const char *Name() override { return "Inspector"; }
		void Awake() override;

	protected:
		void Draw() override;
	};
}

#endif //INSPECTOR_WINDOW_H
