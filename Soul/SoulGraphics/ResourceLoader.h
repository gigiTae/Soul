#pragma once
#include "Vertex.h"

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

		std::shared_ptr<Texture> LoadTexture(const std::wstring& path);

		std::shared_ptr<Shader> LoadShader(const std::wstring& vs
			, const std::wstring& ps
			, const D3D11_INPUT_ELEMENT_DESC* desc
			, UINT descSize);

		std::shared_ptr<GeometryBuffer> LoadGeometryBuffer(const std::wstring& path, Vertex::Type type);

	private:
		void ProcessNode(GeometryBuffer* buffer, const aiNode* node, const aiScene* scene);
		void ProcessMesh(GeometryBuffer* buffer, const aiMesh* mesh, const aiScene* scene);

	private:
		std::unique_ptr<Assimp::Importer> _impoter;

		ResourceManager* _resourceManager;
		std::shared_ptr<Device> _device;
	};
}