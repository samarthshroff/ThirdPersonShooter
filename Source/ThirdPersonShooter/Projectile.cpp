// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	RootComponent = Mesh;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile"));
	ProjectileMovement->InitialSpeed = 500.0f;
	ProjectileMovement->MaxSpeed = 500.0f;

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	Mesh->OnComponentHit.AddDynamic(this, &AProjectile::OnActorHit);	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	AActor* MyOwner = GetOwner();

	if (MyOwner == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("Owner is null"));
		Destroy();
		return;
	}
	
	UE_LOG(LogTemp, Log, TEXT("Owner is NOT null %s"), *MyOwner->GetName());
	AController* OwnerInstigator = MyOwner->GetInstigatorController();
	if (OwnerInstigator == nullptr)
	{
		UE_LOG(LogTemp, Log, TEXT("OwnerInstigator is null"));
	}
	else
	{
		UE_LOG(LogTemp, Log, TEXT("OwnerInstigator is %s"), *(OwnerInstigator->GetName()));
	}
	UE_LOG(LogTemp, Log, TEXT("Other Actor %s"), *(OtherActor->GetName()));
	
	// UClass* DamageType = UDamageType::StaticClass();
	//
	// if (OtherActor && OtherActor != this && OtherActor != Owner)
	// {
	// 	UGameplayStatics::ApplyPointDamage(OtherActor, Damage, Hit.ImpactPoint - StartLocation, Hit, OwnerInstigator,
	// 	 Owner, DamageType);
	// }	
}
