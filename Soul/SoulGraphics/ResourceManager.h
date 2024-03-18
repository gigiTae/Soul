#pragma once


namespace SoulGraphics
{
	class Device;

	class GeometryBuffer;
	class Shader;
	class Texture;

	class ResourceManager
	{
	public:
		using TextureMap = std::unordered_map < std::wstring, std::shared_ptr<Texture>>;
		using ShaderMap = std::unordered_map < std::wstring, std::shared_ptr<Shader>>;
		using GeometryMap = std::unordered_map<std::wstring, std::shared_ptr<GeometryBuffer>>;

		ResourceManager();
		~ResourceManager();

		void Initialize(const std::shared_ptr<Device>& device);
		void Finalize();

		std::shared_ptr<Texture> LoadTexture(const std::wstring& path);
		std::shared_ptr<GeometryBuffer> LoadFBX(const std::wstring& path);
		std::shared_ptr<Shader> LoadShader(const std::wstring& vs, const std::wstring& ps);

		std::shared_ptr<Device> GetDevice()const { return _device; }

	private:
		std::shared_ptr<Device> _device;
		std::unique_ptr<Assimp::Importer> _impoter;
		TextureMap _textureMap;
		ShaderMap _shaderMap;
		GeometryMap _geometryMap;
	};


}