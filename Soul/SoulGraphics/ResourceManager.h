#pragma once

#include "Vertex.h"

namespace SoulGraphics
{
	class Device;

	class ResourceLoader;
	class GeometryBuffer;
	class Shader;
	class Texture;
	class ConstantBuffer;
	class AnimaitonClip;

	class ResourceManager
	{
	public:
		using TextureMap = std::unordered_map < std::wstring, std::shared_ptr<Texture>>;
		using ShaderMap = std::unordered_map < std::wstring, std::shared_ptr<Shader>>;
		using GeometryMap = std::unordered_map<std::wstring, std::shared_ptr<GeometryBuffer>>;
		using AnimationClipMap = std::unordered_map<std::wstring, std::shared_ptr<AnimaitonClip>>;

		ResourceManager();
		~ResourceManager();

		void Initialize(const std::shared_ptr<Device>& device);
		void Finalize();

		std::shared_ptr<Texture> LoadTexture(const std::wstring& path);
		std::shared_ptr<Shader> LoadShader(const std::wstring& vs
			, const std::wstring& ps
			, const D3D11_INPUT_ELEMENT_DESC* desc
			, UINT descSize);
		
		std::shared_ptr<GeometryBuffer> LoadFBX(const std::wstring& path, Vertex::Type type);

		std::shared_ptr<ConstantBuffer> GetConstantBuffer()const { return _constantBuffer; }

		std::shared_ptr<Device> GetDevice()const { return _device; }

	private:
		std::unique_ptr<ResourceLoader> _loader;

		std::shared_ptr<Device> _device;
		std::shared_ptr<ConstantBuffer> _constantBuffer;
		TextureMap _textureMap;
		ShaderMap _shaderMap;
		GeometryMap _geometryMap;
		AnimationClipMap _animationClipMap;
	};


}