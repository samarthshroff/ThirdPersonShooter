// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponActor.h"

#include "Projectile.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	// SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	// RootComponent = SkeletalMesh;		
}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

}

void AWeaponActor::UpdateMesh(const FMeshVariant* NewMesh)
{
	
}

void AWeaponActor::Fire()
{

}



// // Called every frame
// void AWeaponActor::Tick(float DeltaTime)
// {
// 	Super::Tick(DeltaTime);
//
// }

