// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "GunPlayer.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"

AGunPlayer::AGunPlayer()
{
}

void AGunPlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
	playerInputComponent->BindAction("GunOrGrapple", IE_Released, this, &AGunPlayer::SpecialAbility);
}

void AGunPlayer::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("GetActorLocation x= %f,y = %f,  z=%f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	//SpawnPosition = GetActorLocation() + SpawnPositionOffset;
	//UE_LOG(LogTemp, Warning, TEXT("SpawnPosition x= %f,y = %f,  z=%f"), SpawnPosition.X, SpawnPosition.Y, SpawnPosition.Z);
}

void AGunPlayer::SpecialAbility()
{
	if (SpecialAbilityIsReady)
	{
		SpawnPosition = GetActorLocation() + SpawnPositionOffset;
		FVector direction = IsFaceRight ? FVector(1, 0, 0) : FVector(-1, 0, 0);
		FVector EndTrace = SpawnPosition + direction * ShotVelocity;
		//DrawDebugLine(GetWorld(), SpawnPosition, EndTrace, FColor(255, 0, 0), true, 0.f, 0, 5.f);
		FVector directionToGo = FVector(EndTrace.X - SpawnPosition.X, 0, EndTrace.Z - SpawnPosition.Z);
		AProjectile* proj = GetWorld()->SpawnActor<AProjectile>(Projectile, SpawnPosition, FRotator(0, 0, 0));
		proj->SetDirectionToGo(directionToGo);
		//UE_LOG(LogTemp, Warning, TEXT("Pistola usata"));
		SpecialAbilityIsReady = false;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::EnableSpecialAbility, AbilityCooldown, false);
	}
}
