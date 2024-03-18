#pragma once
#include "Resource.h"
#include "Vertex.h"

namespace SoulGraphics
{
	class GeometryBuffer : public Resource
	{
	public:

	public:
		GeometryBuffer(ResourceManager* resMgr);
		~GeometryBuffer();

		void Load(const aiScene* scene, Vertex::Type type);

		ID3D11Buffer* GetVertexBuffer(size_t index) { return _vertexBuffers[index]; }
		ID3D11Buffer* GetIndexBuffer(size_t index) { return _indexBuffers[index]; }
	
		UINT GetVertexSize(size_t index) { return _vertexSizes[index]; }
		UINT GetIndexSize(size_t index) { return _indexSizes[index]; }
		UINT GetMeshSize()const { return _meshSize; }

	private:
		void ProcessNode(aiNode* node, const aiScene* scene);

		void ProcessMesh(aiMesh* mesh, const aiScene* scene);

	private:
		std::vector<UINT> _vertexSizes;
		std::vector<UINT> _indexSizes;
		std::vector<ID3D11Buffer*> _vertexBuffers;
		std::vector<ID3D11Buffer*> _indexBuffers;
		
		UINT _meshSize;
		Vertex::Type _vertexType;
	};
}
