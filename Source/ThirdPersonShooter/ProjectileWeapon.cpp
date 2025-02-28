// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileWeapon.h"

AProjectileWeapon::AProjectileWeapon()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = SkeletalMesh;
}

void AProjectileWeapon::Fire()
{
	Super::Fire();
}

void AProjectileWeapon::UpdateMesh(const FMeshVariant* NewMesh)
{
	Super::UpdateMesh(NewMesh);
	if (NewMesh->Variant != EMeshVariant::SkeletalMesh )
	{
		UE_LOG(LogTemp, Error, TEXT("The provided Argument is not a SkeletalMesh. Please pass a SkeletalMesh"));
		return;
	}

	SkeletalMesh->SetSkeletalMesh(Cast<USkeletalMesh>(NewMesh->GetMesh()));
}

void AProjectileWeapon::BeginPlay()
{
	Super::BeginPlay();
}
