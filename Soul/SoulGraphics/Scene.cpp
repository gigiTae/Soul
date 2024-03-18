#include "SoulGraphicsPCH.h"
#include "Scene.h"
#include "GraphicsEngine.h"
#include "ResourceManager.h"
#include "MeshObject.h"

SoulGraphics::Scene::Scene(GraphicsEngine* engine)
	:_graphicsEngine(engine)
	, _renderingObjects{}
{}

void SoulGraphics::Scene::Initialize()
{
	_graphicsEngine->GetResourceManager();

	MeshObjectInfomation info;
	info.baseColor = L"Resource/boxBaseColor.jpg";
	info.normalMap = L"Resource/boxNormal.jpg";
	info.fbx = L"Resource/box.fbx";

	AddMeshObject(info);
}

void SoulGraphics::Scene::Render(Device* device, RenderState* state, RenderTarget* renderTarget)
{
	for (auto& obj : _renderingObjects)
	{
		obj.second->Render(device, state, renderTarget);
	}
}

void SoulGraphics::Scene::AddMeshObject(const MeshObjectInfomation& info)
{
	auto resMgr = _graphicsEngine->GetResourceManager();

	auto buffer = resMgr->LoadFBX(info.fbx);
	auto baseColor = resMgr->LoadTexture(info.baseColor);
	auto normal = resMgr->LoadTexture(info.normalMap);
	auto shader = resMgr->LoadShader(info.vertexShader, info.pixelShader);

	auto meshObj = std::make_unique<MeshObject>(buffer,shader,normal);

}
