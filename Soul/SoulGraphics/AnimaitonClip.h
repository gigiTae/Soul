#pragma once

namespace SoulGraphics
{
	class AnimaitonClip
	{
	public:
		AnimaitonClip();
		~AnimaitonClip();


	private:
		std::string _name;
		float _duration;
		float _ticksPerSecond;

		std::vector<BoneAnimation> _boneAnimations;
	};
}