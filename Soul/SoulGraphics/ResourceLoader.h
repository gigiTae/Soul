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
	class Animator;

	// 府家胶 肺歹
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

		std::shared_ptr<GeometryBuffer> LoadGeometryBuffer(const aiScene* scene, Vertex::Type type);
		std::shared_ptr<GeometryBuffer> LoadGeometryBufferAndAnimator(const aiScene* scene, Animator* animator);

		std::shared_ptr<AnimaitonClip> LoadAnimationClip(const aiScene* scene);

	private:
		// GeometryBuffer 
		void ProcessNode(GeometryBuffer* buffer, const aiNode* node, const aiScene* scene);
		void ProcessMesh(GeometryBuffer* buffer, const aiMesh* mesh, const aiScene* scene);

		// Animator客 鞍捞 贸府 
		void ProcessNode(GeometryBuffer* buffer, const aiNode* node, const aiScene* scene, Animator* animator);
		void ProcessMesh(GeometryBuffer* buffer, const aiMesh* mesh, const aiScene* scene, Animator* animator);

	private:
		ResourceManager* _resourceManager;
		std::shared_ptr<Device> _device;
	};
}