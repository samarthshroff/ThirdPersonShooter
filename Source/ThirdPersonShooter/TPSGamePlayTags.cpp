// Fill out your copyright notice in the Description page of Project Settings.


#include "TPSGamePlayTags.h"
#include "Engine/EngineTypes.h"
#include "GameplayTagsManager.h"

namespace TPSGameplayTags
{
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(WeaponType_ProjectileEmitter, "Weapon.ProjectileEmitter",
	"A projectile emitter e.g. rifle or pistol.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(WeaponType_Projectile, "Weapon.Projectile", "A projectile e.g. hand grenade.");
	UE_DEFINE_GAMEPLAY_TAG_COMMENT(WeaponType_Melee, "Weapon.Melee", "A melee weapon e.g. heavy sword.");

	FGameplayTag FindTagByString(const FString& TagString, bool bMatchPartialString)
	{
		const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
		FGameplayTag Tag = Manager.RequestGameplayTag(FName(*TagString), false);

		if (!Tag.IsValid() && bMatchPartialString)
		{
			FGameplayTagContainer AllTags;
			Manager.RequestAllGameplayTags(AllTags, true);

			for (const FGameplayTag& TempTag : AllTags)
			{
				if (TempTag.ToString().Contains(TagString))
				{
					UE_LOG(LogTemp, Display, TEXT("Could not find exact tag [%s] but found a partial match on tag [%s]"), *TagString, *TempTag.ToString());
					Tag = TempTag;
					break;
				}
			}
		}
		return Tag;
	}

}
