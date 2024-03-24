#pragma once


namespace SoulGraphics
{
	struct Bone 
	{
		SM::Matrix inverseBindPose;
		std::string name;
	};

	struct Skeleton
	{
		std::vector<Bone> bones;
	};

	struct BonePose
	{
		SM::Quaternion rotation;
		SM::Vector3 position;
		SM::Vector3 scale;
		SM::Matrix transformation = SM::Matrix::Identity;
	};

	struct BoneAnimation
	{
		std::string boneName;
		std::vector<BonePose> bonePoses;
	};

	struct Node
	{
		Node* parent = nullptr;
		std::string_view name;
		std::vector<Node*> children;
		
		SM::Matrix localMatrix = SM::Matrix::Identity;
		SM::Matrix worldMatrix = SM::Matrix::Identity;
	};




}