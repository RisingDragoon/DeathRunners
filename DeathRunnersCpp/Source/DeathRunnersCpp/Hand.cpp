// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "Hand.h"
#include "BasePlatform.h"
#include "GrapplePlayer.h"

AHand::AHand()
{
	UPaperSpriteComponent* sprite = GetRenderComponent();
	sprite->OnComponentBeginOverlap.AddDynamic(this, &AHand::OnBeginOverlap);
}


void AHand::Tick(float DeltaSeconds)
{
	UE_LOG(LogTemp, Warning, TEXT("Tick"));
	if (Move)
	{
		UE_LOG(LogTemp, Warning, TEXT("Si muove"));
		AddActorWorldOffset(DirectionToGo, true);
	}
}

void AHand::SetDirectionToGo(FVector direction, AGrapplePlayer* player)
{
	UE_LOG(LogTemp, Warning, TEXT("SetDirectionToGo"));
	DirectionToGo = FVector(direction.X, 0, direction.Z) * 0.05;
	Move = true;
	//UE_LOG(LogTemp, Warning, TEXT("directionToGo x= %f,y = %f,  z=%f"), direction.X, direction.Y, direction.Z);
	//0.01  lento
	//PlayerName = playerName;
	//DirectionToGo = FVector(direction.X/300, 0,direction.Z/300);
	//SetActorLocation(direction, true);
	//UE_LOG(LogTemp, Warning, TEXT("directionToGo x= %f,y = %f,  z=%f"), direction.X, direction.Y, direction.Z);
}

void AHand::OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap %s"), *OtherActor->GetName());

	//ABasePlatform* hitPlatform = Cast<ABasePlatform>(OtherActor);
	//
	//if (hitPlatform != nullptr)
	//{
	//	//UE_LOG(LogTemp, Warning, TEXT("LOSE CONTROL %s"), *OtherActor->GetName());
	//	UE_LOG(LogTemp, Warning, TEXT("hitPlatform x= %f,y = %f,  z=%f"), hitPlatform->GetActorLocation().X, hitPlatform->GetActorLocation().Y, hitPlatform->GetActorLocation().Z);
	//	UE_LOG(LogTemp, Warning, TEXT("SweepResult.Location x= %f,y = %f,  z=%f"), SweepResult.Location.X, SweepResult.Location.Y, SweepResult.Location.Z);
	//	if (GrapplePlayer)
	//	{
	//		//GrapplePlayer->SetActorLocation()
	//	}
	//	Destroy();
	//}
	UE_LOG(LogTemp, Warning, TEXT("OnBeginOverlap %s"), *OtherActor->GetName());

	ABasePlayer* HitPlayer = Cast<ABasePlayer>(OtherActor);
	AGrapplePlayer* gunPlayer = Cast<AGrapplePlayer>(HitPlayer);

	if (HitPlayer != nullptr && gunPlayer == nullptr)//&& PlayerName != *OtherActor->GetName())// && HitCharacter->GetActorLocation().Z > GetActorLocation().Z + 32.0)
	{
		//UE_LOG(LogTemp, Warning, TEXT("LOSE CONTROL %s"), *OtherActor->GetName());
		HitPlayer->LoseControl();
	}
	if (gunPlayer == nullptr)
	{
		Destroy();
	}
	
}
