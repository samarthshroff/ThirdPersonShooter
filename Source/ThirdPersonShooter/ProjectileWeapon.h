// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponActor.h"
#include "ProjectileWeapon.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AProjectileWeapon : public AWeaponActor
{
	GENERATED_BODY()	

	USkeletalMeshComponent* SkeletalMesh;
	
public:
	AProjectileWeapon();
	void Fire() override;
	void UpdateMesh(const FMeshVariant* NewMesh) override;
protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;	
};
