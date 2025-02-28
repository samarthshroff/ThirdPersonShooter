#pragma once
#include "FMeshVariant.generated.h"

UENUM(BlueprintType)
enum class EMeshVariant : uint8
{
	None UMETA(DisplayName = "None"),
	SkeletalMesh UMETA(DisplayName = "SkeletalMesh"),
	StaticMesh UMETA(DisplayName = "StaticMesh")
};

USTRUCT(BlueprintType)
struct FMeshVariant
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh Variant")
	EMeshVariant Variant;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Variant == EMeshVariant::SkeletalMesh"))
	TObjectPtr<USkeletalMesh> SkeletalMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (EditCondition = "Variant == EMeshVariant::StaticMesh"))
	TObjectPtr<UStaticMesh> StaticMesh;

	void SetSkeletalMesh(TObjectPtr<USkeletalMesh> Mesh);

	void SetStaticlMesh(TObjectPtr<UStaticMesh> Mesh);

	UObject* GetMesh() const;
};
