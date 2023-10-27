#ifndef SCENE_RUNTIME_H
#define SCENE_RUNTIME_H

#include "entt.hpp"

namespace overflow
{
	class Entity;
	class SceneRuntime
	{
	public:
		SceneRuntime();
		~SceneRuntime() = default;

		Entity CreateEntity();
		std::string& Name() { return m_Name; }
		char* Label() { return &m_Name[0]; }

		entt::registry& GetRegistry() { return m_Registry; }

	private:
		entt::registry m_Registry;
		std::string m_Name;

		friend class Entity;
	};
}

#endif //SCENE_RUNTIME_H
