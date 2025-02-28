// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "NativeGameplayTags.h"

namespace TPSGameplayTags
{
	THIRDPERSONSHOOTER_API FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString = false);

	THIRDPERSONSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(WeaponType_ProjectileEmitter);
	THIRDPERSONSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(WeaponType_Projectile);
	THIRDPERSONSHOOTER_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(WeaponType_Melee);
}
