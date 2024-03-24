#pragma once

namespace SoulGraphics
{
	class AnimaitonClip
	{
	public:
		AnimaitonClip();
		~AnimaitonClip();

	private:
		std::vector<BoneAnimation> _boneAnimations;
	
		std::string _name;
		float _duration;
		float _ticksPerSecond;
	};
}