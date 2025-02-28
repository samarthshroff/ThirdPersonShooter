// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectileEmitterWeapon.h"
#include "Projectile.h"


AProjectileEmitterWeapon::AProjectileEmitterWeapon() : Super()
{
	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	RootComponent = SkeletalMesh;
	ProjectileClass = AProjectile::StaticClass();
}

void AProjectileEmitterWeapon::Fire()
{
	Super::Fire();
	if (ProjectileClass)
	{
		// AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, ProjectileSpawnLocation, ProjectileSpawnRotation);
		// Projectile->SetOwner(this);
	}
}

void AProjectileEmitterWeapon::BeginPlay()
{
	Super::BeginPlay();

	ProjectileSpawnLocation = SkeletalMesh->GetSocketLocation(TEXT("Muzzle"));
	ProjectileSpawnRotation = SkeletalMesh->GetSocketRotation(TEXT("Muzzle"));
}

void AProjectileEmitterWeapon::UpdateMesh(const FMeshVariant* NewMesh)
{
	Super::UpdateMesh(NewMesh);
	if (NewMesh->Variant != EMeshVariant::SkeletalMesh )
	{
		UE_LOG(LogTemp, Error, TEXT("The provided Argument is not a SkeletalMesh. Please pass a SkeletalMesh"));
		return;
	}

	SkeletalMesh->SetSkeletalMesh(Cast<USkeletalMesh>(NewMesh->GetMesh()));
}

