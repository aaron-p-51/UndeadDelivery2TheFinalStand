// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"

UCLASS()
class UNDEADDELIVERY2_API AZombie : public ACharacter
{
	GENERATED_BODY()

public:
	

	UPROPERTY(Category = "Zombie", EditAnywhere, BlueprintReadWrite)
	bool bIsCarryingBrain;

};
