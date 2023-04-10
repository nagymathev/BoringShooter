// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnManager.h"

#include "EnemyPawn.h"
#include "Kismet/KismetMathLibrary.h"

ASpawnManager::ASpawnManager()
{
	PrimaryActorTick.bCanEverTick = true;

	Enemies = 0;
	EnemiesToSpawn = 5;
}

void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();

	// SpawnEnemies(EnemiesToSpawn);
}

void ASpawnManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Enemies <= 0)
	{
		SpawnEnemies(EnemiesToSpawn);
	}
	GEngine->AddOnScreenDebugMessage(0, 0.1f, FColor::Red, FString::Printf(TEXT("Enemies: %d"), Enemies));
}

void ASpawnManager::SpawnEnemy()
{
	if (GetWorld())
	{
		FVector SpawnLocation = FVector(UKismetMathLibrary::RandomIntegerInRange(-1500, 1500), UKismetMathLibrary::RandomIntegerInRange(-1500, 1500), 200.f);
		AActor* Enemy = GetWorld()->SpawnActor<AActor>(EnemyClass, SpawnLocation, FRotator::ZeroRotator);
	}
}

void ASpawnManager::SpawnEnemies(int32 Amount)
{
	for (int i = 0; i < Amount; i++)
	{
		SpawnEnemy();
	}
	EnemiesToSpawn += Enemies / 2;
}

