#pragma once

namespace SoulGraphics
{
	class AnimaitonClip
	{
	public:
		AnimaitonClip();
		~AnimaitonClip();

		void Load(const aiAnimation* animation);

		JointPose GetCurrentPose(UINT boneIndex) { return _animationData[_currentIndex][boneIndex]; }
		UINT GetCurrentIndex() { return _currentIndex; }

	private:
		std::string _name;
		UINT _currentIndex;

		std::vector<std::vector<JointPose>> _animationData;
		std::vector<SM::Matrix> _currentMatrix;
	};
}