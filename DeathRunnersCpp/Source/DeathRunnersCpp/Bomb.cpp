// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "Bomb.h"
#include "DrawDebugHelpers.h"
#include "BasePlayer.h"


ABomb::ABomb()
{
	Timer = FTimerHandle();
	//StartTimer();
	//OnComponentBeginOverlap.AddDynamic(this, &ABomb::StartTimer);
}

void ABomb::StartTimer()
{
	//GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABomb::Explode, Countdown, false);
}

void ABomb::Explode()
{
	//UE_LOG(LogTemp, Warning, TEXT("Esplosa"));

	//DestroyPlatformDown();
	//Destroy();
}

FHitResult ABomb::DestroyPlatformDown()
{
	FHitResult hit;
	//FCollisionQueryParams traceParameters(FName(TEXT("")), false, GetOwner());

	//FVector location = GetActorLocation();
	//FVector StartTrace = location;// -ForwardVector * 600;
	//FVector EndTrace = location + FVector::ForwardVector * 600;
	//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(255, 0, 0), false, 0.f, 0, 10.f);
	//GetWorld()->LineTraceSingleByObjectType(hit, StartTrace, EndTrace, FCollisionObjectQueryParams(ECollisionChannel::ECC_Pawn), traceParameters);
	//

	//ABasePlayer actor = (ABasePlayer)hit.;
	//if (actor)
	//{
	//	FString nome = actor->GetName();
	//	UE_LOG(LogTemp, Warning, TEXT("VerticalUp Nome = %s"), *nome)
	//		actor->Destroy();
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("VerticalUp niente"));

	//}
	return hit;
}