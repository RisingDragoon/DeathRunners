// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "GunPlayer.h"
#include "DrawDebugHelpers.h"
#include "PaperFlipbookComponent.h"
#include "Projectile.h"

AGunPlayer::AGunPlayer()
{
}

void AGunPlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
	playerInputComponent->BindAction("SpecialAbility", IE_Released, this, &AGunPlayer::SpecialAbility);
}

void AGunPlayer::StartAnimationShot()
{
	float timeOfAnimation = 0;
	if (Skill)
	{
		timeOfAnimation = Skill->GetTotalDuration();
		SelectedAnimation = PlayerAnimation::Skill;
		UE_LOG(LogTemp, Warning, TEXT("Animazione skill durata= %d"),timeOfAnimation);
		GetWorld()->GetTimerManager().SetTimer(TimerEndAnimation, this, &AGunPlayer::EndAnimationShot, timeOfAnimation, false);
	}
}

void AGunPlayer::EndAnimationShot()
{
	SetSounds(PlayerAnimation::Skill);
	UE_LOG(LogTemp, Warning, TEXT("Fine animazione shot"));
	SelectedAnimation = PlayerAnimation::Nothing;

	SpawnPosition = GetActorLocation() + SpawnPositionOffset;
	FVector direction = IsFaceRight ? FVector(1, 0, 0) : FVector(-1, 0, 0);
	FVector EndTrace = SpawnPosition + direction * ShotVelocity;
	FVector directionToGo = FVector(EndTrace.X - SpawnPosition.X, 0, EndTrace.Z - SpawnPosition.Z);
	AProjectile* proj = GetWorld()->SpawnActor<AProjectile>(Projectile, SpawnPosition, FRotator(0, 0, 0));
	if (proj)
	{
		proj->SetDirectionToGo(directionToGo);
		SpecialAbilityIsReady = false;
		GetWorld()->GetTimerManager().SetTimer(TimerSpecialAbility, this, &ABasePlayer::EnableSpecialAbility, AbilityCooldown, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AProjectile non spawnato"));
	}
}

void AGunPlayer::BeginPlay()
{
	Super::BeginPlay();
}

void AGunPlayer::SpecialAbility()
{
	if (SpecialAbilityIsReady && PlayerToSmash == nullptr)
	{
		StartAnimationShot();
	}
}
