// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayer.h"


#include "EnemyPawn.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Projectile.h"
#include "ShooterGameModeBase.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AShooterPlayer::AShooterPlayer()
{
	PrimaryActorTick.bCanEverTick = true;

	PlayerMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerMesh"));
	RootComponent = PlayerMesh;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("ProjectileSpawnPoint"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);

	PlayerSpeed = 100.f;
}

void AShooterPlayer::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<AShooterGameModeBase>(GetWorld()->GetAuthGameMode());
	PlayerMesh->OnComponentHit.AddDynamic(this, &AShooterPlayer::OnHit);

	if (TObjectPtr<ULocalPlayer> LocalPlayer = Cast<ULocalPlayer>(GetWorld()->GetFirstLocalPlayerFromController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* InputSystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			InputSystem->AddMappingContext(MappingContext, -1);
		}
	}
	
}

void AShooterPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DeltaSeconds = DeltaTime;

	RotatePlayer();
	
	if (!bIsDead && GetActorLocation().Z < -50.f)
	{
		Death();
		bIsDead = true;
	}
}

void AShooterPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	TObjectPtr<UEnhancedInputComponent> Input = Cast<UEnhancedInputComponent>(PlayerInputComponent);

	Input->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AShooterPlayer::MovePlayer);
	Input->BindAction(ShootAction, ETriggerEvent::Triggered, this, &AShooterPlayer::Shoot);

}

void AShooterPlayer::MovePlayer(const FInputActionValue& Value)
{
	FVector2D Direction = Value.Get<FVector2D>();
	Direction.Normalize();
	AddActorWorldOffset(FVector(Direction.X, Direction.Y, 0) * PlayerSpeed * DeltaSeconds);
}

void AShooterPlayer::Shoot(const FInputActionValue& Value)
{
	bool bPressed = Value.Get<bool>();
	if (bPressed)
	{
		const FVector SpawnLocation = ProjectileSpawnPoint->GetComponentLocation();
		const FRotator SpawnRotation = GetActorRotation(); 
		
		FActorSpawnParameters SpawnParams;
		// SpawnParams.Owner = this;
		// SpawnParams.Instigator = this;
		// SpawnParams.Template = Projectile;
		GetWorld()->SpawnActor<AActor>(Projectile, SpawnLocation, SpawnRotation);
	}
}

void AShooterPlayer::RotatePlayer()
{
	// Get the mouse position in the world
	TObjectPtr<APlayerController> PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());
	FVector WorldLocation;
	FVector WorldDirection;
	PlayerController->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);

	// Trace to the mouse position
	FVector TraceEndLocation = WorldLocation + WorldDirection * 5000.f;
	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(GetWorld(), WorldLocation, TraceEndLocation,
		UEngineTypes::ConvertToTraceType(ECC_Visibility), false,
		TArray<AActor*>(), EDrawDebugTrace::ForOneFrame, HitResult, true);

	// Rotate the player to face the mouse position
	FRotator DirectionToLook = UKismetMathLibrary::FindRelativeLookAtRotation(GetActorTransform(), HitResult.ImpactPoint);
	DirectionToLook = FRotator(0, DirectionToLook.Yaw, 0);
	AddActorWorldRotation(DirectionToLook);
}

void AShooterPlayer::Death()
{
	GameMode->PlayerDeath();
}

void AShooterPlayer::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Red, TEXT("Hit") + OtherActor->GetName());
	if (AEnemyPawn* Enemy = Cast<AEnemyPawn>(OtherActor))
	{
		OtherActor->Destroy();
		Death();
	}
}

