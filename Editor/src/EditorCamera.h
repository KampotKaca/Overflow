#ifndef EDITOR_CAMERA_H
#define EDITOR_CAMERA_H

#include "core/utils.h"

namespace overflow
{
	class EditorCamera
	{
	public:
		static constexpr int DEFAULT_ZOOM = 4;
		static constexpr float LOCK_TIME = .5f;
		
		EditorCamera();
		~EditorCamera();
		
		void Update();
		
		[[nodiscard]] mat4 GetView() const;
		[[nodiscard]] mat4 GetProjection(float aspect) const;
		void LockOn(const vec3& target, const vec3& size);
		
		float fov = 45, nearPlane = 0.1f, farPlane = 1000.0f;
	private:
		vec3 m_FocalPoint = {};
		float m_Zoom = DEFAULT_ZOOM * 2;
		vec2 m_Angle = { 0.0f, 0.0f };
		
		bool m_IsLocked = false;
		float m_ZoomTarget = 5.0f;
		vec3 m_FocalTarget = {};
		double_t m_LockTime = 0;
		
		void HandleZoom(float zoomSpeed);
		void HandleLock(float lockOnTime);
		
		void Rotate(const vec2& delta, float rotSpeed);
		void Move(const vec3& dir, float moveSpeed);
	};
}

#endif //EDITOR_CAMERA_H
