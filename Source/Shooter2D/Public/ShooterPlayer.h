// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "ShooterPlayer.generated.h"

class AShooterGameModeBase;
class AProjectile;
class UCameraComponent;
class USpringArmComponent;
class UInputMappingContext;
class UInputAction;

UCLASS()
class SHOOTER2D_API AShooterPlayer : public APawn
{
	GENERATED_BODY()

public:
	AShooterPlayer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MovePlayer(const FInputActionValue& Value);
	void Shoot(const FInputActionValue& Value);
	void RotatePlayer();
	void Death();
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputMappingContext> MappingContext;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> MoveAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TObjectPtr<UInputAction> ShootAction;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	TSubclassOf<AActor> Projectile;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UStaticMeshComponent> PlayerMesh;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<USpringArmComponent> SpringArm;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<UCameraComponent> Camera;
	UPROPERTY(EditAnywhere, BlueprintReadOnly) TObjectPtr<USceneComponent> ProjectileSpawnPoint;

private:
	float DeltaSeconds;
	TObjectPtr<AShooterGameModeBase> GameMode;
	bool bIsDead = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float PlayerSpeed;

};
