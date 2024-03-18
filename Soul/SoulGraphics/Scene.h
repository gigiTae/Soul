#pragma once

#include "IObject.h"

namespace SoulGraphics
{
	class IObject;
	class Camera;
	class GraphicsEngine;

	class Device;
	class RenderState;
	class RenderTarget;

	class Scene
	{
	public:
		using RederingObject = std::pair<std::type_index, std::shared_ptr<IObject>>;

		Scene(GraphicsEngine* engine);
		~Scene() {}

		void Initialize();

		void Render(Device* device, RenderState* state, RenderTarget* renderTarget);

		void AddMeshObject(const MeshObjectInfomation& info);

		template<typename T>
		void AddObject(const std::shared_ptr<T>& object);

	private:
		std::vector<RederingObject> _renderingObjects;
		GraphicsEngine* _graphicsEngine;
	};

	template<typename T>
	void SoulGraphics::Scene::AddObject(const std::shared_ptr<T>& object)
	{
		std::type_index index = std::type_index(typeid(T));
		_renderingObjects.push_back({ index, object });
	}

}