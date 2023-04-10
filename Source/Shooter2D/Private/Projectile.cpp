// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Damageable.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjMesh"));
	ProjMesh->SetupAttachment(RootComponent);

	SetLifeSpan(1.f);
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	ProjMesh->AddImpulse(GetActorUpVector() * ProjectileSpeed);
	ProjMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit);
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, TEXT("Overlap!"));
	if (auto* Enemy = Cast<IDamageable>(OtherActor))
	{
		GEngine->AddOnScreenDebugMessage(0, 1.f, FColor::Red, TEXT("Hit!"));
		Enemy->TakeDamage(1.f);
		Destroy();
	}
}
