#ifndef SCENE_WINDOW_H
#define SCENE_WINDOW_H

#include "EditorWindow.h"

namespace overflow::edit
{
	class SceneWindow : public EditorWindow
	{
	public:
		SceneWindow() = default;
		~SceneWindow() override = default;

		const char *Name() override { return "Scene"; }
		void Awake() override;

	protected:
		void Draw() override;
	};
}

#endif //SCENE_WINDOW_H