#include "SoulGraphicsPCH.h"
#include "Animator.h"
#include "AnimaitonClip.h"

SoulGraphics::Animator::Animator()
	:_root(nullptr)
	, _currentPlayingClipIndex(0)
	, _isLoof(true)
{}

SoulGraphics::Animator::~Animator()
{}

void SoulGraphics::Animator::AddAnimationClip(const std::shared_ptr<AnimaitonClip>& clip)
{
	_animationClips.push_back(clip);
}

const SoulGraphics::CB::BoneMatrix& SoulGraphics::Animator::GetBoneMatrix() const
{
	return _boneMatrix;
}

void SoulGraphics::Animator::Update(float dt)
{
	UpdateAnimation(dt);
	UpdateMatrix();
	UpdateBoneMatrix();
}

void SoulGraphics::Animator::UpdateAnimation(float dt)
{
	const auto& boneAnimations = _animationClips[_currentPlayingClipIndex]->GetBoneAnimations();

	static int i = 0;

	static float d = 0.f;
	d += dt;
	if (d > 1.f)
	{
		d = 0.f; ++i;
	}

	if (i > 67)
	{
		i = 0;
	}

	for (const auto& boneAnimation : boneAnimations)
	{
		auto& localM =_nodeMap[boneAnimation.boneName].localMatrix;

		localM = boneAnimation.bonePoses[i].transformation;
	}
	
}

void SoulGraphics::Animator::UpdateMatrix()
{
	std::queue<Node*> q;
	for (Node* child : _root->children)
	{
		q.push(child);
	}

	while (!q.empty())
	{
		Node* child = q.front();
		Node* parent = child->parent;

		child->worldMatrix = child->localMatrix * parent->worldMatrix;

		for (Node* c : child->children)
		{
			q.push(c);
		}

		q.pop();
	}
}

void SoulGraphics::Animator::UpdateBoneMatrix()
{
	for (UINT i = 0; i < _skelton.bones.size(); ++i)
	{
		auto& inverseBindPose = _skelton.bones[i].inverseBindPose;
		auto& worldM = _nodeMap[_skelton.bones[i].name].worldMatrix;

		_boneMatrix.bone[i] = (inverseBindPose * worldM).Transpose();
	}
}
