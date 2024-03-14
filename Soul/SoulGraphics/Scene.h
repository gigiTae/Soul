#pragma once

#include "IObject.h"

namespace SoulGraphics
{
	class IObject;
	class Camera;

	class Scene
	{
	public:
		using RederingObject = std::pair<std::type_index, std::shared_ptr<IObject>>;

		Scene() {}
		~Scene() {}

		virtual void Initialize() {};

		template<typename T>
		void AddObject(const std::shared_ptr<T>& object);

	private:
		std::vector<RederingObject> _renderingObjects;
	};

	template<typename T>
	void SoulGraphics::Scene::AddObject(const std::shared_ptr<T>& object)
	{
		std::type_index index = std::type_index(typeid(T));
		_renderingObjects.push_back({ index, object });
	}

}