// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FMeshVariant.h"
#include "WeaponGripTypes.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

class AProjectile;
class USkeletalMeshComponent;
 
UCLASS()
class THIRDPERSONSHOOTER_API AWeaponActor : public AActor
{
	GENERATED_BODY()

// protected:
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Graphics, meta=(AllowPrivateAccess = "true"))
// 	FMeshVariant Mesh;
	
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

	int Damage;
	UWeaponGripTypes GripTypes;
	FGameplayTag WeaponType;
	
	// void SetSkeletalMesh(USkeletalMesh* Mesh);
	// USkeletalMeshComponent* GetSkeletalMesh();
	void virtual Fire();
	virtual void UpdateMesh(const FMeshVariant* NewMesh);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	
};
