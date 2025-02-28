#include "FMeshVariant.h"


void FMeshVariant::SetSkeletalMesh(TObjectPtr<USkeletalMesh> Mesh)
{
	SkeletalMesh = Mesh;
	StaticMesh = nullptr;
	Variant = EMeshVariant::SkeletalMesh;
}

void FMeshVariant::SetStaticlMesh(TObjectPtr<UStaticMesh> Mesh)
{
	SkeletalMesh = nullptr;
	StaticMesh = Mesh;
	Variant = EMeshVariant::StaticMesh;
}

UObject* FMeshVariant::GetMesh() const
{
	switch (Variant)
	{
	case EMeshVariant::SkeletalMesh:
		return SkeletalMesh.Get();
	case EMeshVariant::StaticMesh:
		return StaticMesh.Get();
	default:
		return nullptr;
	}
}
