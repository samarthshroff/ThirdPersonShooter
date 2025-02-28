// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "NativeGameplayTags.h"
#include "ProjectileEmitterWeapon.h"
#include "ProjectileWeapon.h"
#include "TPSGamePlayTags.h"
#include "TPSPlayerController.h"
#include "WeaponActor.h"
#include "Kismet/KismetMathLibrary.h"
#include "Logging/StructuredLog.h"

// Sets default values
ATPSCharacter::ATPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	//PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComponent->SetupAttachment(RootComponent);
	// SpringArmComponent->TargetArmLength = 200.0f;
	// SpringArmComponent->SocketOffset = FVector(0.0f, 50.0f, 40.0f);
	// SpringArmComponent->ProbeSize = 12.0f;
	// SpringArmComponent->bUsePawnControlRotation = true;
	
	ThirdPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	ThirdPersonCameraComponent->SetupAttachment(SpringArmComponent);

	// if (WeaponClass == nullptr)
 //    {
 //    	WeaponClass = AWeaponActor::StaticClass();
 //    }
	
	// ThirdPersonCameraComponent->bUsePawnControlRotation = true;
	//
	// GetCharacterMovement()->bUseControllerDesiredRotation = true;
	// GetCharacterMovement()->bOrientRotationToMovement = false;
	//
	// bUseControllerRotationYaw = false;
}

// Called when the game starts or when spawned
void ATPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	WeaponInUseTagIndex = PossessedWeaponsTags.Num()-1;
	
	WeaponDataRetriever = NewObject<UWeaponDataRetriever>();
	
	SpringArmComponent->TargetArmLength = 200.0f;
	SpringArmComponent->SocketOffset = FVector(0.0f, 50.0f, 73.0f);
	SpringArmComponent->ProbeSize = 12.0f;
	SpringArmComponent->bUsePawnControlRotation = true;
	
	ThirdPersonCameraComponent->bUsePawnControlRotation = true;
	
	MovementComponent = MakeShareable(GetCharacterMovement());
	MovementComponent->bUseControllerDesiredRotation = true;
	MovementComponent->bOrientRotationToMovement = false;

	// So that character can strafe.
	bUseControllerRotationYaw = false;

	if (WeaponDataRetriever != nullptr)
	{
		FWeaponMetaData* WeaponData = WeaponDataRetriever->GetWeaponData(PossessedWeaponsTags[WeaponInUseTagIndex].GetTagName());
		
		if (WeaponData->WeaponType == TPSGameplayTags::WeaponType_ProjectileEmitter)
		{
			WeaponActor = GetWorld()->SpawnActor<AProjectileEmitterWeapon>(AProjectileEmitterWeapon::StaticClass());
		}
		if (WeaponData->WeaponType == TPSGameplayTags::WeaponType_Projectile)
		{
			WeaponActor = GetWorld()->SpawnActor<AProjectileWeapon>(AProjectileWeapon::StaticClass());
		}
		if (WeaponActor)
		{
			UE_LOGFMT(LogTemp, Log, "WeaponActor {0}, {1}", WeaponActor->GetName(), WeaponActor->GetFullName());
			WeaponActor->AttachToComponent(GetMesh(),FAttachmentTransformRules::KeepRelativeTransform, "WeaponSocket");
			WeaponActor->UpdateMesh(&(WeaponData->Mesh));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Could not create WeaponActor of type %s"), *(WeaponData->WeaponType.ToString()));
		}
	}	

	if (ATPSPlayerController* PlayerController = Cast<ATPSPlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = 
		ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	AnimInstance = MakeShareable(GetMesh()->GetAnimInstance());	
}

//Called every frame
void ATPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AnimInstance && MovementComponent)
	{
		FName Name = AnimInstance->GetCurrentStateName(0);
		//On Idle mouse rotation rotates the camera to character's front.
		// when not idle mouse rotation moves the character to look in that direction. 
		MovementComponent->bOrientRotationToMovement = Name.Compare("Idle") == 0;
		// if (WeaponActor != nullptr)
		// {
		// 	WeaponActor->GetSkeletalMesh()->SetRelativeTransform()
		// }
	}
}

// Called to bind functionality to input
void ATPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ATPSCharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ATPSCharacter::StopJumping);

		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Look);
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Fire);

		EnhancedInputComponent->BindAction(WeaponChangeAction, ETriggerEvent::Started, this, &ATPSCharacter::ChangeWeapon);
		// EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Fire);
		// EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Triggered, this, &ATPSCharacter::Fire);
	}
}

void ATPSCharacter::ChangeWeapon(const FInputActionValue& InputActionInstance)
{
	UE_LOG(LogTemp, Log, TEXT("The Action on weapon change: "));
}

void ATPSCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MovementVector = Value.Get<FVector2D>();

	FVector RightVector = UKismetMathLibrary::GetRightVector(GetControlRotation());//GetActorRightVector()
	FVector ForwardVector = UKismetMathLibrary::GetForwardVector(GetControlRotation());//GetActorForwardVector()
	
	if (Controller != nullptr)
	{
		AddMovementInput(ForwardVector, MovementVector.Y);
		AddMovementInput(RightVector, MovementVector.X);
	}
}

void ATPSCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ATPSCharacter::Fire(const FInputActionInstance& InputActionInstance)
{
	if (Controller == nullptr) return;

	UE_LOG(LogTemp, Warning, TEXT("FIRE!"));
	if (WeaponActor)
	{
		WeaponActor->Fire();
	}
}

void ATPSCharacter::Jump()
{
	if (Controller == nullptr) return;
	UE_LOG(LogPlayerInput, Log, TEXT("Jump function"));
	Super::Jump();
	JumpButtonDown = CanJump();

	// if (UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent()))
	// {
	// 	double vectorLength = MovementComponent->Velocity.Size();
	// 	if (vectorLength > 0.0f)
	// 	{
	// 		MovementComponent->JumpZVelocity = 400.0f;
	// 	}
	// }
}

void ATPSCharacter::StopJumping()
{
	if (Controller == nullptr) return;
	UE_LOG(LogPlayerInput, Log, TEXT("Stop jumping function"));
	Super::StopJumping();
	JumpButtonDown = false;

	// if (UCharacterMovementComponent* MovementComponent = Cast<UCharacterMovementComponent>(GetMovementComponent()))
	// {
	// 	double vectorLength = MovementComponent->Velocity.Size();
	// 	if (vectorLength > 0.0f)
	// 	{
	// 		MovementComponent->JumpZVelocity = 400.0f;
	// 	}
	// }
}

void ATPSCharacter::OnCharacterIdle()
{
	bIsIdle = true;
}

