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
		//AddActorLocalOffset(DirectionToGo, true);
		AddActorWorldOffset(DirectionToGo, true);
	}
}

void AProjectile::SetDirectionToGo(FVector direction)
{
	DirectionToGo = FVector(direction.X, 0, direction.Z);
	//DirectionToGo = FVector(direction.X/300, 0,direction.Z/300);
	Move = true;
	//SetActorLocation(direction, true);
	//UE_LOG(LogTemp, Warning, TEXT("directionToGo x= %f,y = %f,  z=%f"), direction.X, direction.Y, direction.Z);
}
