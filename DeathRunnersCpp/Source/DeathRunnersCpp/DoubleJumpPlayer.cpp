// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "DoubleJumpPlayer.h"

ADoubleJumpPlayer::ADoubleJumpPlayer()
{

}

void ADoubleJumpPlayer::Jump()
{
	Super::Jump();
	if (JumpCurrentCount==JumpMaxCount)
	{
		StopJumping();
	}
}

void ADoubleJumpPlayer::BeginPlay()
{
	Super::BeginPlay();
	//JumpMaxCount = 2;
	//JumpMaxHoldTime = 0.1;
}

void ADoubleJumpPlayer::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	if (SpecialAbilityIsReady && JumpMaxCount!=2)
	{
		JumpMaxCount = 2;
		JumpMaxHoldTime = 0.1;
	}
	if (JumpCurrentCount == 2)
	{
		SpecialAbilityIsReady = false;
		JumpMaxCount = 1;
		JumpMaxHoldTime = 0.0;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::EnableSpecialAbility, AbilityCooldown, false);
	}
}