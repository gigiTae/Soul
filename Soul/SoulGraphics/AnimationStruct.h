#pragma once


namespace SoulGraphics
{
	struct Joint 
	{
		SM::Matrix inverseBindPose;
		std::string name;
		size_t parent;
	};

	struct Skeleton
	{
		size_t jointCount;
		std::vector<Joint> joints;
	};

	struct JointPose
	{
		SM::Quaternion rotation;
		SM::Vector3 position;
		SM::Vector3 scale;
	};

	struct SkeletonPose
	{
		std::vector<Skeleton> skeleton;
		std::vector<JointPose> jointPose;
		std::vector<SM::Matrix> globalPose;
	};

}