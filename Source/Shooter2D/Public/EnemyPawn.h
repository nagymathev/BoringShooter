// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Damageable.h"
#include "GameFramework/Pawn.h"
#include "EnemyPawn.generated.h"

class ASpawnManager;
class AShooterPlayer;
UCLASS()
class SHOOTER2D_API AEnemyPawn : public APawn, public IDamageable
{
	GENERATED_BODY()

public:
	AEnemyPawn();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void TakeDamage(float Damage) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	TObjectPtr<UStaticMeshComponent> EnemyMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
	float EnemySpeed = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	TSubclassOf<AActor> PlayerTarget;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Target")
	TSubclassOf<AActor> SpawnManagerTarget;

private:
	TObjectPtr<AActor> Player;
	TObjectPtr<ASpawnManager> SpawnManager;
};
