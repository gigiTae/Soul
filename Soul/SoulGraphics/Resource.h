#pragma once

namespace SoulGraphics
{
	class ResourceManager;

	class Resource
	{
	public:
		Resource(ResourceManager* resMgr)
			:_resourceManager(resMgr)
		{}

		virtual ~Resource() {}

		ResourceManager* GetResourceManager()const { return _resourceManager; }
	private:
		ResourceManager* _resourceManager;
	};
}