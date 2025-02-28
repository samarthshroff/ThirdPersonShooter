// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponActor.h"
#include "ProjectileEmitterWeapon.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API AProjectileEmitterWeapon : public AWeaponActor
{
	GENERATED_BODY()

	TSubclassOf<AProjectile> ProjectileClass;

	FVector ProjectileSpawnLocation;
	FRotator ProjectileSpawnRotation;

	int NumberOfBulletsPerMag;
	float IntervalBetweenBulletsShot;
	USkeletalMeshComponent* SkeletalMesh;
	
public:
	AProjectileEmitterWeapon();
	void Fire() override;
	void UpdateMesh(const FMeshVariant* NewMesh) override;
protected:
	// Called when the game starts or when spawned
	void BeginPlay() override;
	
	
};
