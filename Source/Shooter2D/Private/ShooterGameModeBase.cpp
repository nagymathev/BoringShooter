// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterGameModeBase.h"

#include "Blueprint/UserWidget.h"

AShooterGameModeBase::AShooterGameModeBase()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AShooterGameModeBase::PlayerDeath()
{
	if (DefaultDeathScreenWidgetClass)
	{
		DeathScreenWidget = CreateWidget<UUserWidget>(GetWorld(), DefaultDeathScreenWidgetClass);
		if (DeathScreenWidget) DeathScreenWidget->AddToViewport();
		
		if (PlayerController) PlayerController->bShowMouseCursor = true;
		FInputModeUIOnly InputMode;
		if (PlayerController) PlayerController->SetInputMode(InputMode);
	}
}

void AShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = false;
	FInputModeGameOnly InputMode;
	PlayerController->SetInputMode(InputMode);
}

void AShooterGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
