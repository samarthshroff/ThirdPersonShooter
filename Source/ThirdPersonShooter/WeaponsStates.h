#pragma once

UENUM(BlueprintType)
enum class UProjectileEmitterState : uint8
{
	NOT_PICKED UMETA(DisplayName = "NotPicked"),
	IDLE UMETA(DisplayName = "Idle"), // when not possessed
	READY_TO_FIRE UMETA(DisplayName = "ReadyToFire"),
	FIRING UMETA(DisplayName = "Firing"),
	RELOAD UMETA(DisplayName = "Reload"),
	RELOADING UMETA(DisplayName = "Reloading"),
	NO_AMMO UMETA(DisplayName = "NoAmmo")
};

UENUM(BlueprintType)
enum class UProjectileState : uint8
{
	NOT_PICKED UMETA(DisplayName = "NotPicked"),
	IDLE UMETA(DisplayName = "Idle"), // when not possessed
	READY_TO_FIRE UMETA(DisplayName = "ReadyToFire"),
	NO_AMMO UMETA(DisplayName = "NoAmmo")
};

UENUM(BlueprintType)
enum class UMeleeState : uint8
{
	IDLE UMETA(DisplayName = "Idle"), // when not possessed
	READY_TO_ATTACK UMETA(DisplayName = "ReadyToAttack"),
	ATTACKING UMETA(DisplayName = "Attacking")
};
