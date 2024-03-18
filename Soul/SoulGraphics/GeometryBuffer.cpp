#include "SoulGraphicsPCH.h"
#include "GeometryBuffer.h"

SoulGraphics::GeometryBuffer::GeometryBuffer(ResourceManager* resMgr)
	:Resource(resMgr)
	,_meshSize(0)
	,_vertexType(Vertex::Type::MeshVertex)
	,_vertexSizes{}
	,_indexSizes{}
	,_vertexBuffers{}
	,_indexBuffers{}
{

}

SoulGraphics::GeometryBuffer::~GeometryBuffer()
{

}

void SoulGraphics::GeometryBuffer::Load(const aiScene* scene)
{
	

}
