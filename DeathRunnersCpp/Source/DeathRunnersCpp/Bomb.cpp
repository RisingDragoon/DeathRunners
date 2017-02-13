// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "Bomb.h"



ABomb::ABomb()
{
	Timer = FTimerHandle();
	StartTimer();
}

void ABomb::StartTimer()
{
	GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABomb::Explode, Countdown, false);
}

void ABomb::Explode()
{

}