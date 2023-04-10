// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

class AEnemyPawn;
UCLASS()
class SHOOTER2D_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	ASpawnManager();
	int32 Enemies;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	void SpawnEnemy();
	void SpawnEnemies(int32 Amount);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	TSubclassOf<AEnemyPawn> EnemyClass;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	int32 EnemiesToSpawn;
};
