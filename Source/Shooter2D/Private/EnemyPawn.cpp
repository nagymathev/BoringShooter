// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyPawn.h"

#include "ShooterGameModeBase.h"
#include "ShooterPlayer.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnManager.h"

AEnemyPawn::AEnemyPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	EnemyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyMesh"));
	RootComponent = EnemyMesh;
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();
	
	Player = UGameplayStatics::GetActorOfClass(GetWorld(), PlayerTarget);
	SpawnManager = Cast<ASpawnManager>(UGameplayStatics::GetActorOfClass(GetWorld(), SpawnManagerTarget));

	if (SpawnManager)
	{
		SpawnManager->Enemies++;
	}
}

void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player)
	{
		FVector TargetDirection = (Player->GetActorLocation() - GetActorLocation());
		TargetDirection.Normalize();

		AddActorWorldOffset(TargetDirection * EnemySpeed * DeltaTime);
	}

	if (GetActorLocation().Z < -50.f)
	{
		Destroy();
		if (SpawnManager) SpawnManager->Enemies--;
	}
}

void AEnemyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyPawn::TakeDamage(float Damage)
{
	Destroy();
	// AShooterGameModeBase* GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
	// if (GameMode)
	// {
	// }
	if (SpawnManager)
	{
		SpawnManager->Enemies--;
	}
}

