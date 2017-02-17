// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "BomberPlayer.h"


void ABomberPlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
	playerInputComponent->BindAction("Bomb", IE_Pressed, this, &ABomberPlayer::SpecialAbility);
}

void ABomberPlayer::SpecialAbility()
{
	FActorSpawnParameters SpawnParams;
	//GetWorld()->SpawnActor<ABomb>(GetActorLocation(), GetActorRotation(), SpawnParams);
}