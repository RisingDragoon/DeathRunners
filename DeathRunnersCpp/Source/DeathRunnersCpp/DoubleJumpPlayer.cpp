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
	JumpMaxCount = 2;
	JumpMaxHoldTime = 0.1;
}