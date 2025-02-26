// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayTagsWrapper.h"

#include "GameplayTagsManager.h"

void UGameplayTagsWrapper::AddGameplayTag(FName GameplayTagName,const FString& Comment)
{
	FGameplayTag Tag = UGameplayTagsManager::Get().RequestGameplayTag(GameplayTagName, false);
	
	if (Tag.IsValid())
	{
		UE_LOG(LogTemp, Error, TEXT("Gameplay Tag %s already exists"), *GameplayTagName.ToString());
		return;
	}
	
	UGameplayTagsManager::Get().AddNativeGameplayTag(GameplayTagName, Comment);	
	UE_LOG(LogTemp, Display, TEXT("Gameplay Tag %s added with comment: %s"), *GameplayTagName.ToString(), *Comment);
}

void UGameplayTagsWrapper::AddGameplayTags(const TArray<FName>& GameplayTagsName, const TArray<FString>& Comments)
{
	const UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	for (int32 i = 0; i < GameplayTagsName.Num(); i++)
	{
		FName TagName = GameplayTagsName[i];
		FString Comment = Comments[i];
		FGameplayTag Tag = Manager.RequestGameplayTag(TagName, false);
		if (Tag.IsValid())
		{
			UE_LOG(LogTemp, Error, TEXT("Gameplay Tag %s already exists"), *(TagName.ToString()));
			continue;
		}

		UGameplayTagsManager::Get().AddNativeGameplayTag(TagName, Comment);
		UE_LOG(LogTemp, Display, TEXT("Gameplay Tag %s added with comment: %s"), *TagName.ToString(), *Comment);
	}
}
