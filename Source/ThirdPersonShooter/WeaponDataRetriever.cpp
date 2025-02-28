// Fill out your copyright notice in the Description page of Project Settings.

#include "WeaponDataRetriever.h"

UWeaponDataRetriever::UWeaponDataRetriever()
{	
	static ConstructorHelpers::FObjectFinder<UDataTable> AllWeaponsDataTable(TEXT("/Game/DataTables/DT_AllWeaponsData.DT_AllWeaponsData"));

	if (AllWeaponsDataTable.Succeeded())
	{
		AllWeaponsData = AllWeaponsDataTable.Object;
	}
}

UWeaponDataRetriever::~UWeaponDataRetriever()
{
	AllWeaponsData = nullptr;
}

FWeaponMetaData* UWeaponDataRetriever::GetWeaponData(const FName& RowName) const
{
	FString ContextString = "Could not find the row %s" + RowName.ToString();
	TArray<FString> Parsed;
	RowName.ToString().ParseIntoArray(Parsed, TEXT("."));
	UE_LOG(LogTemp, Log, TEXT("The RowName() %s"), *(Parsed.Last()));
	
	return AllWeaponsData->FindRow<FWeaponMetaData>(FName(*(Parsed.Last())),ContextString, true);
}
