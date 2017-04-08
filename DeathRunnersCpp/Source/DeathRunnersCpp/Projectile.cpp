// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "Projectile.h"
#include "GunPlayer.h"

AProjectile::AProjectile()
{
	UPaperSpriteComponent* sprite = GetRenderComponent();
	sprite->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
}

void AProjectile::Tick(float DeltaSeconds)
{
	if (Move)
	{
		AddActorWorldOffset(DirectionToGo, true);
	}
}

void AProjectile::SetDirectionToGo(FVector direction)
{
	DirectionToGo = FVector(direction.X, 0, direction.Z);
	Move = true;
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap %s"), *OtherActor->GetName());

	ABasePlayer* HitPlayer = Cast<ABasePlayer>(OtherActor);
	AGunPlayer* gunPlayer = Cast<AGunPlayer>(HitPlayer);
	
	if (HitPlayer != nullptr && gunPlayer==nullptr)
	{
		HitPlayer->ReceiveShot();
	}
	if (gunPlayer == nullptr)
	{
		Destroy();
	}
}

