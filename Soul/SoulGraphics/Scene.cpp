#include "SoulGraphicsPCH.h"
#include "Scene.h"
#include "GraphicsEngine.h"
#include "ResourceManager.h"
#include "MeshObject.h"
#include "Camera.h"
#include "ConstantBuffer.h"
#include "Material.h"
#include "Vertex.h"
#include "SkinnedMeshObject.h"
#include "Animator.h"

SoulGraphics::Scene::Scene(GraphicsEngine* engine)
	:_graphicsEngine(engine)
	, _renderingObjects{}
{}

void SoulGraphics::Scene::Initialize()
{
	_graphicsEngine->GetResourceManager();

	// Mesh Object
	MeshObjectInfomation info;
	info.baseColor = L"Resource/character.png";
	info.normalMap = L"Resource/character_normal.png";
	info.fbx = L"Resource/Character.fbx";
	info.pixelShader = L"MeshPS.hlsl";
	info.vertexShader = L"MeshVS.hlsl";

	//AddMeshObject(info);

	// SkinnedMeshObject
	info.pixelShader = L"SkinningMeshPS.hlsl";
	info.vertexShader = L"SkinningMeshVS.hlsl";
	info.fbx = L"Resource/SkinningTest.fbx";
	AddSkinnedMeshObject(info);
}

void SoulGraphics::Scene::Update(float dt)
{
	for (auto& obj : _renderingObjects)
	{
		obj.second->Update(dt);
	}

}

void SoulGraphics::Scene::Render(Device* device, RenderState* state, RenderTarget* renderTarget)
{
	UpdateLight();

	for (auto& obj : _renderingObjects)
	{
		static float r = 0.f;
		r += 0.001f;

		obj.second->SetWorldTM(SM::Matrix::CreateRotationY(r));

		//		obj.second->SetWorldTM(SM::Matrix::Identity);
		obj.second->SetViewProjTM(_graphicsEngine->GetCamera());
		obj.second->Render(device, state, renderTarget);
	}
}

void SoulGraphics::Scene::AddMeshObject(const MeshObjectInfomation& info)
{
	auto resMgr = _graphicsEngine->GetResourceManager();

	auto geometryBuffer = resMgr->LoadGeometryBuffer(info.fbx, Vertex::Type::MeshVertex);
	auto constantBuffer = resMgr->GetConstantBuffer();
	auto shader = resMgr->LoadShader(info.vertexShader
		, info.pixelShader
		, Vertex::InputLayoutDesc::MeshVertex
		, Vertex::InputLayoutDesc::MeshVertexArraySize);

	// Texture, Material 생성
	auto baseColor = resMgr->LoadTexture(info.baseColor);
	auto normal = resMgr->LoadTexture(info.normalMap);
	auto material = std::make_shared<Material>(baseColor, normal);

	auto meshObj = std::make_shared<MeshObject>(geometryBuffer, constantBuffer, shader, material);

	_renderingObjects.push_back({ std::type_index(typeid(MeshObject)), meshObj });
}

void SoulGraphics::Scene::AddSkinnedMeshObject(const MeshObjectInfomation& info)
{
	auto resMgr = _graphicsEngine->GetResourceManager();

	// FBX로드
	auto animator = std::make_unique<Animator>();
	auto geometryBuffer = resMgr->LoadGeometryBufferAndAnimator(info.fbx, animator.get());

	auto constantBuffer = resMgr->GetConstantBuffer();
	auto shader = resMgr->LoadShader(info.vertexShader
		, info.pixelShader
		, Vertex::InputLayoutDesc::SkinnedVertex
		, Vertex::InputLayoutDesc::SkinnedVertexArraySize);

	// Texture, Material 생성
	auto baseColor = resMgr->LoadTexture(info.baseColor);
	auto normal = resMgr->LoadTexture(info.normalMap);
	auto material = std::make_shared<Material>(baseColor, normal);

	auto meshObj = std::make_shared<SkinnedMeshObject>(geometryBuffer
		, constantBuffer
		, shader
		, material
		, std::move(animator));

	_renderingObjects.push_back({ std::type_index(typeid(SkinnedMeshObject)), meshObj });
}

void SoulGraphics::Scene::UpdateLight()
{
	_lightInfo.lightColor[0] = SM::Vector4(0.f, 0.f, 0.f, 1.f);
	_lightInfo.lightColor[1] = SM::Vector4(0.f, 1.f, 1.f, 1.f);

	auto cameraPos = _graphicsEngine->GetCamera()->GetPosition();
	cameraPos.Normalize();

	_lightInfo.lightDirection[0] = SM::Vector4(cameraPos);

	static float d;

	d += 0.0001f;

	SM::Vector4 v(sinf(d), 1.f, cosf(d), 0.f);
	v.Normalize();

	_lightInfo.lightDirection[1] = v;

	_graphicsEngine->GetResourceManager()->GetConstantBuffer()->BindLightCB(_lightInfo);
}
