#ifndef SCENE_WINDOW_H
#define SCENE_WINDOW_H

#include "EditorWindow.h"
#include "rendering/FrameBuffer.h"
#include "EditorCamera.h"

namespace overflow::edit
{
	class SceneWindow : public EditorWindow
	{
	public:
		SceneWindow() = default;
		~SceneWindow() override = default;

		const char *Name() override { return "Scene"; }
		void Awake() override;
		
	private:
		ref<FrameBuffer> m_Buffer = nullptr;
		ref<EditorCamera> m_Camera = nullptr;
		ImVec2 m_Size = { 512, 512 };
		
		void Draw() override;
	};
}

#endif //SCENE_WINDOW_H