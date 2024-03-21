#include "SoulGraphicsPCH.h"
#include "SkinnedMeshObject.h"
#include "Camera.h"
#include "Device.h"
#include "RenderState.h"
#include "RenderTarget.h"
#include "Shader.h"
#include "Texture.h"
#include "GeometryBuffer.h"
#include "ConstantBufferStruct.h"
#include "ConstantBuffer.h"
#include "Material.h"
#include "AnimaitonClip.h"

SoulGraphics::SkinnedMeshObject::SkinnedMeshObject(std::shared_ptr<GeometryBuffer> gb
	, std::shared_ptr<ConstantBuffer> cb
	, std::shared_ptr<Shader> shader
	, std::shared_ptr<Material> material
	, std::shared_ptr<AnimaitonClip> aniClip)
	:_geometryBuffer(gb)
	, _constantBuffer(cb)
	, _shader(shader)
	, _material(material)
	, _animationClip(aniClip)
	, _worldTM{}
	, _viewTM{}
	, _projTM{}
{}

SoulGraphics::SkinnedMeshObject::~SkinnedMeshObject()
{}

void SoulGraphics::SkinnedMeshObject::Render(Device* device, RenderState* state, RenderTarget* renderTarget)
{
	auto deviceContext = device->GetDeviceContext();

	// 애니메이션 설정q
	SetAnimationClip();

	// Matrix 상수버퍼 설정
	_constantBuffer->BindMatrixCB(_worldTM, _viewTM, _projTM);
	_shader->BindShader();
	_material->BindTexture(0, Material::Type::BaseColor);
	_material->BindTexture(1, Material::Type::Normal);

	state->BindRasterizerState(RenderState::Rasterizer::Solid);
	state->BindSamplerState(0, RenderState::Sampler::LINEAR);

	for (UINT i = 0; i < _geometryBuffer->GetMeshSize(); ++i)
	{
		// 정점, 인덱스 버퍼 생성
		_geometryBuffer->BindVertexAndIndexBuffer(i);

		deviceContext->DrawIndexed(_geometryBuffer->GetIndexSize(i), 0, 0);
	}
}

DirectX::SimpleMath::Matrix SoulGraphics::SkinnedMeshObject::GetWorldTM() const
{
	return _worldTM;
}

void SoulGraphics::SkinnedMeshObject::SetWorldTM(const DirectX::SimpleMath::Matrix& mat)
{
	_worldTM = mat;
}

void SoulGraphics::SkinnedMeshObject::SetViewProjTM(Camera* camera)
{
	_viewTM = camera->GetViewTM();
	_projTM = camera->GetProjTM();
}

void SoulGraphics::SkinnedMeshObject::SetGeometryBuffer(const std::shared_ptr<GeometryBuffer>& buffer)
{
	_geometryBuffer = buffer;

}

std::shared_ptr<SoulGraphics::GeometryBuffer> SoulGraphics::SkinnedMeshObject::GetGeometryBuffer()
{
	return _geometryBuffer;
}

void SoulGraphics::SkinnedMeshObject::SetAnimationClip()
{
	auto& boneMatix = _constantBuffer->GetBoneMatrix();
	UINT boneSize = _geometryBuffer->GetBoneSize();

	for (UINT i = 0; i < boneSize; ++i)
	{
		auto pose = _animationClip->GetCurrentPose(i);

		auto pos = SM::Matrix::CreateTranslation(pose.position);
		auto rot = SM::Matrix::CreateFromQuaternion(pose.rotation);
		auto scale = SM::Matrix::CreateScale(pose.scale);

		SM::Matrix boneWorldMatrix = scale * rot * pos;
		boneMatix.bone[i] = (_geometryBuffer->GetInverseBindPose(i) * boneWorldMatrix).Transpose();
	}

	_constantBuffer->BindBoneMatrixCB();
}
