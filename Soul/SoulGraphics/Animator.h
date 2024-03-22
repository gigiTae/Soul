#pragma once

namespace SoulGraphics
{
	class AnimaitonClip;

	class Animator
	{
	public:
		Animator();
		~Animator();
		
	private:
		std::vector<std::shared_ptr<AnimaitonClip>> _animationClips;
	};
}

