// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameplayTagsWrapper.generated.h"

struct FGameplayTag;
/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTEREDITOR_API UGameplayTagsWrapper : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Python|GameplayTags")
	static void AddGameplayTag(FName GameplayTagName, const FString& Comment);

	UFUNCTION(BlueprintCallable, Category = "Python|GameplayTags")
	static void AddGameplayTags(const TArray<FName>& GameplayTagsName, const TArray<FString>& Comments);	
};
