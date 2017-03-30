// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "Hand.h"
#include "GrapplePlayer.h"
#include "BasePlatform.h"

AHand::AHand()
{
	UPaperSpriteComponent* sprite = GetRenderComponent();
	sprite->OnComponentBeginOverlap.AddDynamic(this, &AHand::OnBeginOverlap);
}


void AHand::Tick(float DeltaSeconds)
{
	if (Move)
	{
		AddActorWorldOffset(DirectionToGo, true);
	}
}

void AHand::SetDirectionToGo(FVector direction, AGrapplePlayer* player)
{
	DirectionToGo = FVector(direction.X, 0, direction.Z) * 0.05;
	Move = true;
	GrapplePlayer = player;
	//0.01  lento
	//PlayerName = playerName;
	//DirectionToGo = FVector(direction.X/300, 0,direction.Z/300);
	//SetActorLocation(direction, true);
	//UE_LOG(LogTemp, Warning, TEXT("directionToGo x= %f,y = %f,  z=%f"), direction.X, direction.Y, direction.Z);
}

void AHand::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap %s"), *OtherActor->GetName());
	ABasePlatform* hitPlatform = Cast<ABasePlatform>(OtherActor);

	if (hitPlatform != nullptr)
	{
		//UE_LOG(LogTemp, Warning, TEXT("hitPlatform x= %f,y = %f,  z=%f"), hitPlatform->GetActorLocation().X, hitPlatform->GetActorLocation().Y, hitPlatform->GetActorLocation().Z);
		//UE_LOG(LogTemp, Warning, TEXT("SweepResult.Location x= %f,y = %f,  z=%f"), SweepResult.Location.X, SweepResult.Location.Y, SweepResult.Location.Z);
		if (GrapplePlayer)
		{
			FVector location = FVector(SweepResult.Location.X, 0, SweepResult.Location.Z + 100);
			GrapplePlayer->SetActorLocation(location);
			Destroy();
		}
	}
	AGrapplePlayer* HitPlayer = Cast<AGrapplePlayer>(OtherActor);
	if (!HitPlayer)
	{
		Destroy();
	}
}
