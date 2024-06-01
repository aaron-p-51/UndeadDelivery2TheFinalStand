// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ZombieSpawnManager.generated.h"

class AZombieSpawnZone;
class AZombie;

USTRUCT(BLueprintType)
struct FActorDistanceFromPoint
{
	GENERATED_BODY()

	UPROPERTY()
	AActor* Actor;

	UPROPERTY()
	float DistanceSqr;
};


UCLASS()
class UNDEADDELIVERY2_API AZombieSpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AZombieSpawnManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(Category = "ZombieSpawnManager", BlueprintCallable)
	FVector GetActorCollectionCenter(const TArray<AActor*>& Actors);

	UFUNCTION(Category = "ZombieSpawnManager", BlueprintCallable)
	class AZombieSpawnZone* GetNextZombieSpawnZone(const TArray<AZombieSpawnZone*> ZombieSpawnVolumes, const FVector& CurrentZombiesCenter, AZombieSpawnZone* LastSpawnZone, float DirectionFromCenter);

	//void PrintAllZombieSpawnZoneFromPlayer(const TArray<FZombieSpawnZoneFromPlayer>& Zones) const;

	UFUNCTION(Category = "ZombieSpawnManager", BlueprintCallable)
	void SortByDistanceFromPoint(const FVector& Point, TArray<AActor*> Actors, TArray<AActor*>& SortedActors);

protected:

	//UPROPERTY(Category = "ZombieSpawnManager", EditAnywhere, BlueprintReadWrite)
	//TArray<AZombie*> SpawnedZombies; 

};
