// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ShooterGameModeBase.generated.h"

class ASpawnManager;
class AEnemyPawn;
/**
 * 
 */
UCLASS()
class SHOOTER2D_API AShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	AShooterGameModeBase();

	void PlayerDeath();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UMG")
	TSubclassOf<UUserWidget> DefaultDeathScreenWidgetClass;
	TObjectPtr<UUserWidget> DeathScreenWidget;

	TObjectPtr<APlayerController> PlayerController;

};
