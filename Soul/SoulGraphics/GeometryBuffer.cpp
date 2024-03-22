#include "SoulGraphicsPCH.h"
#include "GeometryBuffer.h"
#include "ResourceManager.h"
#include "Device.h"


SoulGraphics::GeometryBuffer::GeometryBuffer(ResourceManager* resMgr, Vertex::Type type)
	:Resource(resMgr)
	, _meshSize(0)
	, _vertexType(type)
	, _vertexSizes{}
	, _indexSizes{}
	, _vertexBuffers{}
	, _indexBuffers{}
	, _vertexBufferStride{}
	, _vertexBufferOffset(0)
{}

SoulGraphics::GeometryBuffer::~GeometryBuffer()
{}

void SoulGraphics::GeometryBuffer::BindVertexAndIndexBuffer(size_t index)
{
	auto deviceContext = GetResourceManager()->GetDevice()->GetDXDeviceContext();

	deviceContext->IASetIndexBuffer(_indexBuffers[index], DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffers[index], &_vertexBufferStride, &_vertexBufferOffset);
}


