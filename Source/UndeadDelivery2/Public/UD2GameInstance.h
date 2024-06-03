// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UD2GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class UNDEADDELIVERY2_API UUD2GameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	UFUNCTION(Category = "UD2GameInstance", BlueprintCallable)
	void SetVSyncEnabled(bool bEnable);
	
};
