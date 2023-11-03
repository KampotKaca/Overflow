#ifndef HIERARCHY_WINDOW_H
#define HIERARCHY_WINDOW_H

#include "EditorWindow.h"

namespace overflow::edit
{
	class HierarchyWindow : public EditorWindow
	{
	public:
		HierarchyWindow() = default;
		~HierarchyWindow() override = default;

		void Awake() override;
		static Entity GetSelection();

	protected:
		void Draw() override;
		const char* Name() override { return "Hierarchy"; }
	};
}

#endif //HIERARCHY_WINDOW_H
