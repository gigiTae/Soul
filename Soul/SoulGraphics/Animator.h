#pragma once

#include "ConstantBufferStruct.h"

namespace SoulGraphics
{
	class AnimaitonClip;
	class ResourceLoader;

	class Animator
	{
	public:
		Animator();
		~Animator();

		void AddAnimationClip(const std::shared_ptr<AnimaitonClip>& clip);
	
		const CB::BoneMatrix& GetBoneMatrix()const;

		void Update(float dt);

	private:
		void UpdateAnimation(float dt);
		void UpdateMatrix();
		void UpdateBoneMatrix();

	private:
		Skeleton _skelton;
		std::map<std::string, UINT> _boneMapping;
		std::unordered_map<std::string, Node> _nodeMap;
		Node* _root;

		std::vector<std::shared_ptr<AnimaitonClip>> _animationClips;
		CB::BoneMatrix _boneMatrix;

		// Animation 재생 관련
		bool _isLoof;
		UINT _currentPlayingClipIndex;

		friend class ResourceLoader;
	};
}

