// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "Projectile.h"

AProjectile::AProjectile()
{
}

void AProjectile::Tick(float DeltaSeconds)
{
	if (Move)
	{
		//FVector direction = FVector(DirectionToGo.X * DeltaSeconds, 0, DirectionToGo.Z * DeltaSeconds);// *Speed;
		//SetActorLocation(direction, true);
	}
}

void AProjectile::SetDirectionToGo(FVector direction)
{
	DirectionToGo = direction;
	Move = true;
	SetActorLocation(direction, true);
}
