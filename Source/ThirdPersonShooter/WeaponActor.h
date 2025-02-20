// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponActor.generated.h"

class USkeletalMeshComponent;

UCLASS()
class THIRDPERSONSHOOTER_API AWeaponActor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Graphics, meta=(AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;
public:	
	// Sets default values for this actor's properties
	AWeaponActor();

	void SetSkeletalMesh(USkeletalMesh* Mesh);
	USkeletalMeshComponent* GetSkeletalMesh();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
