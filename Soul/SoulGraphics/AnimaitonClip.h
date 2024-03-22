#pragma once

namespace SoulGraphics
{
	class AnimaitonClip
	{
	public:
		AnimaitonClip();
		~AnimaitonClip();

		void Load(const aiScene* scene);
		void LoadAnimation(const aiAnimation* animation);

		JointPose GetCurrentPose(UINT boneIndex) { return _animationData[_currentIndex][boneIndex]; }
		UINT GetCurrentIndex() { return _currentIndex; }

	private:
		void ProcessNode(const aiNode* node, const aiScene* scene);

	private:
		std::string _name;
		UINT _currentIndex;

		std::vector<std::vector<JointPose>> _animationData;
		std::vector<SM::Matrix> _currentMatrix;
	};
}