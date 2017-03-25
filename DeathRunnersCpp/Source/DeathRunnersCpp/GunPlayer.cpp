// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "GunPlayer.h"
#include "DrawDebugHelpers.h"
#include "Projectile.h"

AGunPlayer::AGunPlayer()
{
}

void AGunPlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	Super::SetupPlayerInputComponent(playerInputComponent);
	playerInputComponent->BindAction("FireGun", IE_Released, this, &AGunPlayer::SpecialAbility);
	playerInputComponent->BindAxis("FireGunX", this, &AGunPlayer::LogX);
	playerInputComponent->BindAxis("FireGunY", this, &AGunPlayer::LogY);
}

void AGunPlayer::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(LogTemp, Warning, TEXT("GetActorLocation x= %f,y = %f,  z=%f"), GetActorLocation().X, GetActorLocation().Y, GetActorLocation().Z);
	//SpawnPosition = GetActorLocation() + SpawnPositionOffset;
	//UE_LOG(LogTemp, Warning, TEXT("SpawnPosition x= %f,y = %f,  z=%f"), SpawnPosition.X, SpawnPosition.Y, SpawnPosition.Z);
}

void AGunPlayer::SpecialAbility()
{
	if (SpecialAbilityIsReady)
	{
		if (LastAxisY >= 0)
		{
			FVector direzione = FVector(LastAxisX, 0, LastAxisY);
			SpawnPosition = GetActorLocation() + SpawnPositionOffset;
			FVector EndTrace = SpawnPosition + direzione * 300;
			direzione = SpawnPosition + direzione;
			//DrawDebugLine(GetWorld(), SpawnPosition, EndTrace, FColor(255, 0, 0), true, 0.f, 0, 5.f);
			AProjectile* proj = GetWorld()->SpawnActor<AProjectile>(Projectile, SpawnPosition, FRotator());
			FVector directionToGo = FVector(EndTrace.X - SpawnPosition.X, 0, EndTrace.Z - SpawnPosition.Z);

			//FVector directionToGo = FVector(direzione.X , 0, direzione.Z);
			//UE_LOG(LogTemp, Warning, TEXT("StartTrace x= %f,y = %f,  z=%f"), StartTrace.X, StartTrace.Y, StartTrace.Z);
			//UE_LOG(LogTemp, Warning, TEXT("EndTrace x= %f,y = %f,  z=%f"), EndTrace.X, EndTrace.Y, EndTrace.Z);
			//FVector directionToGo = location + 600;
			//directionToGo.Y = 0;
			//UE_LOG(LogTemp, Warning, TEXT("directionToGo x= %f,y = %f,  z=%f"), directionToGo.X, directionToGo.Y, directionToGo.Z);
			proj->SetDirectionToGo(directionToGo, GetName());
			UE_LOG(LogTemp, Warning, TEXT("Pistola usata"));
			SpecialAbilityIsReady = false;
			GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::EnableSpecialAbility, AbilityCooldown, false);
		}
	}
}


void AGunPlayer::LogX(float value)
{
	if (value == 0 && LastAxisY==0)
	{
		return;
	}
	if (value !=LastAxisX)
	{
		LastAxisX = value;
		if (SpecialAbilityIsReady)
		{
			//SpecialAbility();
		}
		//UE_LOG(LogTemp, Warning, TEXT("AXIS X: %f"), LastAxisX);//X
	}
}

void AGunPlayer::LogY(float value)
{
	if (value == 0 && LastAxisX == 0)
	{
		return;
	}
	if (value != LastAxisY)
	{
		LastAxisY = -value;
		if (SpecialAbilityIsReady)
		{
			//SpecialAbility();
		}
		//UE_LOG(LogTemp, Warning, TEXT("AXIS Y: %f"), LastAxisY);//Z
	}
}