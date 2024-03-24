#pragma once

namespace SoulGraphics
{
	class ResourceLoader;

	class AnimaitonClip
	{
	public:
		AnimaitonClip();
		~AnimaitonClip();

		const std::vector<BoneAnimation>& GetBoneAnimations()const { return _boneAnimations; }

	private:
		std::vector<BoneAnimation> _boneAnimations;
	
		std::string _name;
		float _duration;
		float _ticksPerSecond;

		friend class ResourceLoader;
	};
}