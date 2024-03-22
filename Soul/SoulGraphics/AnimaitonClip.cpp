#include "SoulGraphicsPCH.h"
#include "AnimaitonClip.h"

SoulGraphics::AnimaitonClip::AnimaitonClip()
	:_currentIndex(0)
{}

SoulGraphics::AnimaitonClip::~AnimaitonClip()
{

}

void SoulGraphics::AnimaitonClip::Load(const aiScene* scene)
{
	ProcessNode(scene->mRootNode, scene);
}


void SoulGraphics::AnimaitonClip::LoadAnimation(const aiAnimation* animation)
{
	UINT channel = animation->mNumChannels;

	_animationData.resize(channel);

	for (UINT i = 0; i < channel; ++i)
	{
		const aiNodeAnim* nodeAnim = animation->mChannels[i];

		auto numClip = nodeAnim->mNumPositionKeys;

		auto n = nodeAnim->mNodeName;

		assert(!(nodeAnim->mNumPositionKeys == nodeAnim->mNumRotationKeys == nodeAnim->mNumScalingKeys));

		_animationData[i].resize(numClip);

		for (UINT j = 0; j < numClip; j++)
		{
			auto& jointPose = _animationData[i][j];

			auto pos = nodeAnim->mPositionKeys[j].mValue;
			auto rot = nodeAnim->mRotationKeys[j].mValue;
			auto scale = nodeAnim->mScalingKeys[j].mValue;

			jointPose.time = nodeAnim->mScalingKeys[j].mTime;
			jointPose.position = { pos.x, pos.y, pos.z };
			jointPose.rotation = { rot.x, rot.y, rot.z, rot.w };
			jointPose.scale = { scale.x, scale.y, scale.z };
		}
	}
}

void SoulGraphics::AnimaitonClip::ProcessNode(const aiNode* node, const aiScene* scene)
{
	for (UINT i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
	}

	for (UINT i = 0; i < node->mNumChildren; i++) {
		ProcessNode(node->mChildren[i], scene);
	}
}
