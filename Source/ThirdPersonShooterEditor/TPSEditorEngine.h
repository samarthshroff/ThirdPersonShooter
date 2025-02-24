// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Editor/UnrealEdEngine.h"
#include "TPSEditorEngine.generated.h"

class IEngineLoop;
class UObject;

/**
 * 
 */
UCLASS()
class THIRDPERSONSHOOTEREDITOR_API UTPSEditorEngine : public UUnrealEdEngine
{
	GENERATED_BODY()
protected:
	virtual void Init(IEngineLoop* InEngineLoop) override;
	virtual void Start() override;
public:
	UTPSEditorEngine(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
