// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "InputAction.h"
#include "WeaponDataRetriever.h"
#include "WeaponMetaData.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "TPSCharacter.generated.h"

class AWeaponActor;
struct FInputActionValue;
class UInputAction;
class UInputMappingContext;
class UCameraComponent;

UCLASS()
class THIRDPERSONSHOOTER_API ATPSCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> ThirdPersonCameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> SpringArmComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> FireAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UInputAction> WeaponChangeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	bool JumpButtonDown;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Weapon, meta = (AllowPrivateAccess = "true"))
	TArray<FGameplayTag> PossessedWeaponsTags;
		
	UPROPERTY(VisibleInstanceOnly, Category=Weapon, meta=(AllowPrivateAccess = "true"))
	TObjectPtr<AWeaponActor> WeaponActor;

	UPROPERTY()
	TObjectPtr<UWeaponDataRetriever> WeaponDataRetriever;

	UFUNCTION(BlueprintCallable, Category = CharacterState, meta = (AllowPrivateAccess = "true"))
	void OnCharacterIdle();

	bool bIsIdle;
	
	int WeaponInUseTagIndex;
	TSharedPtr<UAnimInstance> AnimInstance;
	TSharedPtr<UCharacterMovementComponent> MovementComponent;
	
public:
	// Sets default values for this character's properties
	ATPSCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Fire(const FInputActionInstance& InputActionInstance);
	void ChangeWeapon(const FInputActionValue& InputActionInstance);

	void Jump() override;
	void StopJumping() override;

 public:	
 	// Called every frame
 	virtual void Tick(float DeltaTime) override;
};
