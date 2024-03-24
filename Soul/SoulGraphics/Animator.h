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


	private:
		std::vector<std::unique_ptr<Node>> _nodeVector;

		std::vector<std::shared_ptr<AnimaitonClip>> _animationClips;
		CB::BoneMatrix _boneMatrix;

		std::map<std::string, UINT> _boneMapping;

		friend class ResourceLoader;
	};
}

