#pragma once
#include "Resource.h"
#include "Vertex.h"
#include "Device.h"
#include "ResourceManager.h"

namespace SoulGraphics
{
	class ResourceLoader;

	class GeometryBuffer : public Resource
	{
	public:
		friend class ResourceLoader;

	public:
		GeometryBuffer(ResourceManager* resMgr, Vertex::Type type);
		~GeometryBuffer();

		ID3D11Buffer* GetVertexBuffer(size_t index) { return _vertexBuffers[index]; }
		ID3D11Buffer* GetIndexBuffer(size_t index) { return _indexBuffers[index]; }
	
		UINT GetVertexSize(size_t index) { return _vertexSizes[index]; }
		UINT GetIndexSize(size_t index) { return _indexSizes[index]; }
		UINT GetMeshSize()const { return _meshSize; }

		void BindVertexAndIndexBuffer(size_t index);

		template <typename VertexType>
		void CreateVertexAndIndex(const std::vector<VertexType>& vertices, const std::vector<UINT> indices);

	private:
		std::vector<UINT> _vertexSizes;
		std::vector<UINT> _indexSizes;
		std::vector<ID3D11Buffer*> _vertexBuffers;
		std::vector<ID3D11Buffer*> _indexBuffers;
		
		UINT _meshSize;
		UINT _vertexBufferStride;
		UINT _vertexBufferOffset;

		Vertex::Type _vertexType;
	};

	template <typename VertexType>
	void SoulGraphics::GeometryBuffer::CreateVertexAndIndex(const std::vector<VertexType>& vertices, const std::vector<UINT> indices)
	{
		++_meshSize;
		auto dxDevice = GetResourceManager()->GetDevice()->GetDXDevice();

		D3D11_BUFFER_DESC vbd;
		vbd.Usage = D3D11_USAGE_IMMUTABLE;
		vbd.ByteWidth = static_cast<UINT>(sizeof(VertexType) * vertices.size());
		vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		vbd.CPUAccessFlags = 0;
		vbd.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		initData.pSysMem = &vertices[0];

		ID3D11Buffer* vertexBuffer = nullptr;
		ID3D11Buffer* indexBuffer = nullptr;

		HR_T(dxDevice->CreateBuffer(&vbd, &initData, &vertexBuffer));

		D3D11_BUFFER_DESC ibd;
		ibd.Usage = D3D11_USAGE_IMMUTABLE;
		ibd.ByteWidth = static_cast<UINT>(sizeof(UINT) * indices.size());
		ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
		ibd.CPUAccessFlags = 0;
		ibd.MiscFlags = 0;

		initData.pSysMem = &indices[0];

		HR_T(dxDevice->CreateBuffer(&ibd, &initData, &indexBuffer));

		_vertexBufferOffset = 0;
		_vertexBufferStride = sizeof(VertexType);
		_vertexSizes.push_back(vertices.size());
		_indexSizes.push_back(indices.size());
		_vertexBuffers.push_back(vertexBuffer);
		_indexBuffers.push_back(indexBuffer);
	}

}
