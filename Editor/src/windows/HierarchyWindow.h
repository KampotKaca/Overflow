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

	protected:
		void Draw() override;
		const char* Name() override { return "Hierarchy"; }

	private:
	};
}

#endif //HIERARCHY_WINDOW_H
