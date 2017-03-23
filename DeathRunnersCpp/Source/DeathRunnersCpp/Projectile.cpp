// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "Projectile.h"
#include "BasePlayer.h"

AProjectile::AProjectile()
{
	UPaperSpriteComponent* sprite = GetRenderComponent();
	sprite->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::OnBeginOverlap);
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

void AProjectile::SetDirectionToGo(FVector direction, FString playerName)
{
	DirectionToGo = FVector(direction.X, 0, direction.Z);
	Move = true;
	PlayerName = playerName;
	//DirectionToGo = FVector(direction.X/300, 0,direction.Z/300);
	//SetActorLocation(direction, true);
	//UE_LOG(LogTemp, Warning, TEXT("directionToGo x= %f,y = %f,  z=%f"), direction.X, direction.Y, direction.Z);
}

void AProjectile::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//Se colpisce un player lo stunna
	/*if (OtherActor)
	{
		UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap %s"), *OtherActor->GetName());
	}*/
	UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap %s"), *OtherActor->GetName());
	//UE_LOG(LogTemp, Warning, TEXT("PlayerName %s"), *PlayerName);
	ABasePlayer* HitPlayer = Cast<ABasePlayer>(OtherActor);
	if (HitPlayer != nullptr && PlayerName != *OtherActor->GetName())// && HitCharacter->GetActorLocation().Z > GetActorLocation().Z + 32.0)
	{
		UE_LOG(LogTemp, Warning, TEXT("LOSE CONTROL %s"), *OtherActor->GetName());
		HitPlayer->LoseControl();
	}
	//Move = false;
	Destroy();
}

