// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieSpawnZone.generated.h"

class UBoxComponent;


UCLASS()
class UNDEADDELIVERY2_API AZombieSpawnZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieSpawnZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(Category = "ZombieSpawnZone", EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UBoxComponent> SpawnZone;

	

public:	

	bool CanBeSeenByPlayer(APlayerController* PlayerController) const;
};
