// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieSpawnManager.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "ZombieSpawnZone.h"
#include "Algo/Sort.h"

// Sets default values
AZombieSpawnManager::AZombieSpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AZombieSpawnManager::BeginPlay()
{
	Super::BeginPlay();
	
}

FVector AZombieSpawnManager::GetActorCollectionCenter(const TArray<AActor*>& Actors)
{
	if (Actors.IsEmpty())
	{
		return FVector::ZeroVector;
	}

	FVector ActorPositionSum = FVector::ZeroVector;
	for (const auto Actor : Actors)
	{
		ActorPositionSum += Actor->GetActorLocation();
	}

	return ActorPositionSum / Actors.Num();
}


AZombieSpawnZone* AZombieSpawnManager::GetNextZombieSpawnZone(const TArray<AZombieSpawnZone*> ZombieSpawnVolumes, const FVector& CurrentZombiesCenter, AZombieSpawnZone* LastSpawnZone, float DirectionFromCenter)
{
	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	if (!PlayerController)
	{
		return nullptr;
	}

	APawn* PlayerPawn = PlayerController->GetPawn();
	if (!PlayerPawn)
	{
		return nullptr;
	}

	const FVector PlayerLocation = PlayerPawn->GetActorLocation();
	const FVector DirectionToZombieCenter = (CurrentZombiesCenter - PlayerLocation).GetSafeNormal();

	TArray<FActorDistanceFromPoint> PossibleSpawnZones;

	for (const auto ZombieSpawnZone : ZombieSpawnVolumes)
	{
		if (ZombieSpawnZone && ZombieSpawnZone != LastSpawnZone)
		{
			const FVector DirectionToSpawnZone = (ZombieSpawnZone->GetActorLocation() - PlayerLocation).GetSafeNormal();
			if (FVector::DotProduct(DirectionToZombieCenter, DirectionToSpawnZone) < DirectionFromCenter)
			{
				if (!ZombieSpawnZone->CanBeSeenByPlayer(PlayerController))
				{
					float DistanceSqrToSpawnZone = (ZombieSpawnZone->GetActorLocation() - PlayerLocation).SquaredLength();
					PossibleSpawnZones.Add(FActorDistanceFromPoint(ZombieSpawnZone, DistanceSqrToSpawnZone));
				}
			}
		}
	}

	// No possible spawn zones
	if (PossibleSpawnZones.Num() == 0)
	{
		return nullptr;
	}

	Algo::Sort(PossibleSpawnZones, [](const auto& A, const auto& B)
		{
			return A.DistanceSqr < B.DistanceSqr;
		});

	if (PossibleSpawnZones.Num() == 1)
	{
		return Cast<AZombieSpawnZone>(PossibleSpawnZones[0].Actor);
	}
	
	return	Cast<AZombieSpawnZone>(PossibleSpawnZones[FMath::RandRange(0, 1)].Actor);
}


void AZombieSpawnManager::SortByDistanceFromPoint(const FVector& Point, TArray<AActor*> Actors, TArray<AActor*>& SortedActors)
{
	TArray<FActorDistanceFromPoint> ActorDistanceFromPoint;
	for (const auto Actor : Actors)
	{
		const float DistanceSqrToPoint = (Point - Actor->GetActorLocation()).SquaredLength();
		ActorDistanceFromPoint.Add(FActorDistanceFromPoint(Actor, DistanceSqrToPoint));
	}

	Algo::Sort(ActorDistanceFromPoint, [](const auto& A, const auto& B)
		{
			return A.DistanceSqr < B.DistanceSqr;
		});


	for (const auto Actor : ActorDistanceFromPoint)
	{
		SortedActors.Add(Actor.Actor);
	}
	
}

//void AZombieSpawnManager::PrintAllZombieSpawnZoneFromPlayer(const TArray<FZombieSpawnZoneFromPlayer>& Zones) const
//{
//	UE_LOG(LogTemp, Warning, TEXT("PrintAllZombieSpawnZoneFromPlayer"));
//
//	for (const auto Zone : Zones)
//	{
//		UE_LOG(LogTemp, Warning, TEXT("Name: %s, Distance: %f"), *Zone.ZombieSpawnZone->GetName(), Zone.DistanceSqrToPlayer);
//	}
//}



