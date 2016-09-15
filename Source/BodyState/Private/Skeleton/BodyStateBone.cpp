
#include "BodyStatePrivatePCH.h"
#include "BodyStateUtility.h"
#include "BodyStateBone.h"

UBodyStateBone::UBodyStateBone(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Alpha = 0.f;
}

FVector UBodyStateBone::Position()
{
	return BoneData.Transform.GetTranslation();
}


void UBodyStateBone::SetPosition(const FVector& InPosition)
{
	BoneData.Transform.SetTranslation(InPosition);
}

FRotator UBodyStateBone::Orientation()
{
	return BoneData.Transform.GetRotation().Rotator();
}


void UBodyStateBone::SetOrientation(const FRotator& InOrientation)
{
	BoneData.Transform.SetRotation(InOrientation.Quaternion());
}

FVector UBodyStateBone::Scale()
{
	return BoneData.Transform.GetScale3D();
}


void UBodyStateBone::SetScale(const FVector& InScale)
{
	BoneData.Transform.SetScale3D(InScale);
}


void UBodyStateBone::InitializeFromBoneData(const FBodyStateBoneData& InData)
{
	//Set the bone data
	BoneData = InData;

	//Re-initialize default values
}

bool UBodyStateBone::Enabled()
{
	return Alpha == 1.f;
}

void UBodyStateBone::SetEnabled(bool enable)
{
	enable ? Alpha = 1.f: Alpha = 0.f;
}

void UBodyStateBone::ShiftBone(FVector Shift)
{
	BoneData.Transform.SetTranslation(BoneData.Transform.GetTranslation() + Shift);
}

void UBodyStateBone::ChangeBasis(FRotator PreBase, FRotator PostBase, bool AdjustVectors)
{
	//Adjust the orientation
	FRotator PostCombine = CombineRotators(Orientation(), PostBase);
	BoneData.Transform.SetRotation(FQuat(CombineRotators(PreBase, PostCombine)));

	//Rotate our vector/s
	if (AdjustVectors)
	{
		BoneData.Transform.SetTranslation(PostBase.RotateVector(Position()));
	}
}

bool UBodyStateBone::IsTracked()
{
	return BoneData.Confidence > 0.f;
}
