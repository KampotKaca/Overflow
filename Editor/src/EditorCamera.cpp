#include <imgui.h>
#include "pch.h"
#include "EditorCamera.h"
#include "core/time.h"

namespace overflow
{
	EditorCamera::EditorCamera() = default;
	EditorCamera::~EditorCamera() = default;
	
	void EditorCamera::Update()
	{
		if(m_IsLocked) HandleLock(LOCK_TIME);
	}
	
	mat4 EditorCamera::GetView() const
	{
		vec2 radians = glm::radians(m_Angle);
		vec3 forward, right, up;
		glm::camera_directions(m_Angle, right, up, forward);
		return glm::lookAt(m_FocalPoint - forward * m_Zoom, m_FocalPoint, up);
	}
	
	mat4 EditorCamera::GetProjection(float aspect) const
	{
		return glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);
	}
	
	void EditorCamera::LockOn(const vec3 &target, const vec3 &size)
	{
		m_FocalTarget = target;
		m_IsLocked = true;
		m_ZoomTarget = glm::max(size.z, glm::max(size.x, size.y)) * DEFAULT_ZOOM;
		m_LockTime = Time::GetUTime();
	}
	
	void EditorCamera::Rotate(const vec2 &delta, float rotSpeed)
	{
		float deltaTime = Time::UDeltaF();
		m_Angle.x -= delta.x * rotSpeed * deltaTime;
		m_Angle.y -= delta.y * rotSpeed * deltaTime;
		m_Angle.y = glm::clamp(m_Angle.y, -89.999f, 89.999f);
		m_Angle.x = glm::mod(m_Angle.x, 360.0f);
	}
	
	void EditorCamera::Move(const vec3 &dir, float moveSpeed)
	{
		float deltaTime = Time::UDeltaF();
		
		vec3 right, up, forward;
		glm::camera_directions(m_Angle, right, up, forward);
		
		m_FocalPoint += forward * (moveSpeed * dir.z * deltaTime);
		m_FocalPoint += right * (moveSpeed * dir.x * deltaTime);
		m_FocalPoint += up * (moveSpeed * dir.y * deltaTime);
	}
	
	void EditorCamera::HandleZoom(float zoomSpeed)
	{
		ImGuiIO& io = ImGui::GetIO();
		m_Zoom = glm::lerp(m_Zoom, 0, io.MouseWheel * zoomSpeed * Time::UDeltaF());
	}
	
	void EditorCamera::HandleLock(float lockOnTime)
	{
		double_t passedPercent = (Time::GetUTime() - m_LockTime) / lockOnTime;
		passedPercent = glm::clamp(passedPercent, 0.0, 1.0);
		m_Zoom = glm::lerp(m_Zoom, m_ZoomTarget, (float)passedPercent);
		m_FocalPoint = glm::lerp(m_FocalPoint, m_FocalTarget, (float)passedPercent);
		
		if(glm::abs(1.0 - passedPercent) < 0.00001) m_IsLocked = false;
	}
}