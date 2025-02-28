// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponMetaData.h"
#include "UObject/NoExportTypes.h"
#include "WeaponDataRetriever.generated.h"

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTER_API UWeaponDataRetriever : public UObject
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<class UDataTable> AllWeaponsData;

public:
	UWeaponDataRetriever();
	~UWeaponDataRetriever();

	FWeaponMetaData* GetWeaponData(const FName& RowName) const;
};
