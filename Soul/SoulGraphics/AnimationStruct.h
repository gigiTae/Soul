#pragma once


namespace SoulGraphics
{
	struct Bone 
	{
		SM::Matrix inverseBindPose;
		std::string name;
		size_t parent;
	};

	struct Skeleton
	{
		size_t jointCount;
		std::vector<Bone> joints;
	};

	struct BonePose
	{
		SM::Quaternion rotation;
		SM::Vector3 position;
		SM::Vector3 scale;
		SM::Matrix local;
	};

	struct BoneAnimation
	{
		size_t boneIndex;
		std::string boneName;
		std::vector<BonePose> bonePoses;
	};

	struct SkeletonPose
	{
		Skeleton skeleton;
		std::vector<BonePose> jointPose;
		std::vector<SM::Matrix> globalPose;
	};

	struct Node
	{
		size_t parent;
		std::vector<size_t> children;

		std::string name;
		
		SM::Matrix localMatrix;
		SM::Matrix worldMatrix;
		
		SM::Vector3 position;
		SM::Quaternion rotation;
		SM::Vector3 scale;
	};




}