#pragma once

#include "FMeshVariant.h"
#include "GameplayTagsManager.h"
#include "WeaponGripTypes.h"
#include "WeaponMetaData.generated.h"

USTRUCT(BlueprintType)
struct FWeaponMetaData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int NumberOfBulletsPerMag;

	UPROPERTY(EditAnywhere)
	int DamageInPrecentage;

	UPROPERTY(EditAnywhere)
	int DefaultPossessionValue;

	UPROPERTY(EditAnywhere)
	float IntervalBetweenBulletsShot;

	UPROPERTY(EditAnywhere)
	bool CanActorPossesSecondWeapon;
	
	UPROPERTY(EditAnywhere)
	UWeaponGripTypes GripType;

	UPROPERTY(EditAnywhere)
	FGameplayTag WeaponType;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AProjectile> Projectile;
	
	UPROPERTY(EditAnywhere)
	FMeshVariant Mesh;
};
