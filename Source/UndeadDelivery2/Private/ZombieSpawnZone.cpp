// Fill out your copyright notice in the Description page of Project Settings.


#include "ZombieSpawnZone.h"

#include "Components/BoxComponent.h"

// Sets default values
AZombieSpawnZone::AZombieSpawnZone()
{
	SpawnZone = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnZone"));
	SpawnZone->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AZombieSpawnZone::BeginPlay()
{
	Super::BeginPlay();
	
}

bool AZombieSpawnZone::CanBeSeenByPlayer(APlayerController* PlayerController) const
{
	if (!SpawnZone || !PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("Wrong Params"));
		return false;
	}

	const FVector BoxExtent = SpawnZone->GetScaledBoxExtent();
	const FTransform BoxTransform = SpawnZone->GetComponentTransform();

	// All box verticies
	TArray<FVector> BoxVerticies;
	BoxVerticies.Add(FVector(BoxExtent.X, BoxExtent.Y, BoxExtent.Z));
	BoxVerticies.Add(FVector(BoxExtent.X, BoxExtent.Y, -BoxExtent.Z));
	BoxVerticies.Add(FVector(BoxExtent.X, -BoxExtent.Y, BoxExtent.Z));
	BoxVerticies.Add(FVector(BoxExtent.X, -BoxExtent.Y, -BoxExtent.Z));
	BoxVerticies.Add(FVector(-BoxExtent.X, BoxExtent.Y, BoxExtent.Z));
	BoxVerticies.Add(FVector(-BoxExtent.X, BoxExtent.Y, -BoxExtent.Z));
	BoxVerticies.Add(FVector(-BoxExtent.X, -BoxExtent.Y, BoxExtent.Z));
	BoxVerticies.Add(FVector(-BoxExtent.X, -BoxExtent.Y, -BoxExtent.Z));

	// Transform Vertex to world space
	for (FVector& Vertex : BoxVerticies)
	{
		Vertex = BoxTransform.TransformPosition(Vertex);
	}

	// Get player view
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	PlayerController->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(PlayerController->GetPawn());

	for (const auto Vertex : BoxVerticies)
	{
		FHitResult HitResult;
		if (!GetWorld()->LineTraceSingleByChannel(HitResult, PlayerViewPointLocation, Vertex, ECollisionChannel::ECC_Visibility, CollisionQueryParams))
		{
			return true;	
		}
	}

	return false;
}



