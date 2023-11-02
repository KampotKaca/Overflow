#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <utility>
#include "core/utils.h"
#include "assets/Mesh.h"
#include "assets/Material.h"
#include "rendering/RenderStructure.h"

namespace overflow
{
	struct IDComponent
	{
		IDComponent() = default;
		IDComponent(IDComponent&) = default;
		IDComponent(std::string name, UUID uuid = UUID())
			:Name(std::move(name)), ID(uuid) {}
		~IDComponent() = default;

		operator UUID() const { return ID; }

		std::string Name = "Entity";
	private:
		UUID ID;
	};

	struct Transform
	{
		Transform() = default;
		Transform(Transform&) = default;
		Transform(vec3 pos, vec3 rot = { 0, 0, 0 }, vec3 scale = { 1, 1, 1 })
		: Position(pos), Rotation(rot), Scale(scale) {}
		~Transform() = default;

		operator mat4() const
		{
			return glm::scale(glm::translate(mat4(1.0f), Position) *
					glm::toMat4(quat(Rotation)), Scale);
		}

		vec3 Position = { 0, 0, 0 },
			 Rotation = { 0, 0, 0 },
			 Scale = { 1, 1, 1 };

		entt::entity Parent = entt::null;
	};

	struct ChildComponent
	{
		ChildComponent() = default;
		ChildComponent(ChildComponent&) = default;
		~ChildComponent() = default;

		std::vector<entt::entity> Children;
	};

	struct Render2D
	{
		Render2D() = default;
		Render2D(Render2D&) = default;
		~Render2D() = default;


		vec4 Color = vec4(1);
		Tex2D* Texture = nullptr;
		Material* Material = nullptr;
		bool CastShadows = true;
	};

	struct Render3D
	{
		Render3D() = default;
		Render3D(Render3D&) = default;
		~Render3D() = default;

		Mesh* Mesh = nullptr;
		Material* Material = nullptr;
		bool CastShadows = true;
	};
}

#endif //COMPONENTS_H
