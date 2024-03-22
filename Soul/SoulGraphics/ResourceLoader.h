#pragma once

namespace SoulGraphics
{
	class ResourceManager;
	class Device;
	class GeometryBuffer;
	class Shader;
	class Texture;
	class ConstantBuffer;
	class AnimaitonClip;

	// 리소스 로더
	class ResourceLoader
	{
	public:
		ResourceLoader();

		void Initialize(ResourceManager* resMgr,std::shared_ptr<Device> device);

		std::shared_ptr<Texture> LoadTexture(const std::wstring path);
	private:
		ResourceManager* _resourceManager;
		std::shared_ptr<Device> _device;
	};
}