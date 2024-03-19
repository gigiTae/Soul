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
	info.pixelShader = L"BasicPS.hlsl";
	info.vertexShader = L"BasicVS.hlsl";

	AddMeshObject(info);
}

void SoulGraphics::Scene::Render(Device* device, RenderState* state, RenderTarget* renderTarget)
{
	for (auto& obj : _renderingObjects)
	{
		using namespace DirectX::SimpleMath;

		static float r = 0.f;
		r += 0.0001f;
		Matrix m_World = DirectX::XMMatrixRotationX(r);

		obj.second->SetWorldTM(m_World);
		obj.second->SetViewProjTM(_graphicsEngine->GetCamera());
		obj.second->Render(device, state, renderTarget);
	}
}

void SoulGraphics::Scene::AddMeshObject(const MeshObjectInfomation& info)
{
	auto resMgr = _graphicsEngine->GetResourceManager();

	auto geometryBuffer = resMgr->LoadFBX(info.fbx);
	auto constantBuffer = resMgr->GetConstantBuffer();
	auto baseColor = resMgr->LoadTexture(info.baseColor);
	auto normal = resMgr->LoadTexture(info.normalMap);
	auto shader = resMgr->LoadShader(info.vertexShader, info.pixelShader);

	auto meshObj = std::make_shared<MeshObject>(geometryBuffer, constantBuffer, shader, baseColor);

	_renderingObjects.push_back({ std::type_index(typeid(MeshObject)), meshObj});

}
