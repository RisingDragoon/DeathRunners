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
	playerInputComponent->BindAction("GunOrGrapple", IE_Released, this, &AGunPlayer::SpecialAbility);
	playerInputComponent->BindAxis("AxisX", this, &AGunPlayer::LogX);
	playerInputComponent->BindAxis("AxisY", this, &AGunPlayer::LogY);
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
			FVector direction = FVector(LastAxisX, 0, LastAxisY);
			SpawnPosition = GetActorLocation() + SpawnPositionOffset;
			FVector EndTrace = SpawnPosition + direction * 15;// *300;
			direction = SpawnPosition + direction;
			//DrawDebugLine(GetWorld(), SpawnPosition, EndTrace, FColor(255, 0, 0), true, 0.f, 0, 5.f);
			float base = EndTrace.X - SpawnPosition.X;
			float altezza = EndTrace.Z - SpawnPosition.Z;
			base = (base > 0) ? base : -base;
			altezza = (altezza > 0) ? altezza : -altezza;

			float value = sqrt(pow(2,(base))+pow(2,(altezza)));
			UE_LOG(LogTemp, Warning, TEXT("Modulo %f"), value);

			if (value > MinValueShot)
			{
				AProjectile* proj = GetWorld()->SpawnActor<AProjectile>(Projectile, SpawnPosition, FRotator(0, 0, 0));
				FVector directionToGo = FVector(EndTrace.X - SpawnPosition.X, 0, EndTrace.Z - SpawnPosition.Z);
				proj->SetDirectionToGo(directionToGo, GetName());
				UE_LOG(LogTemp, Warning, TEXT("Pistola usata"));
				SpecialAbilityIsReady = false;
				GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABasePlayer::EnableSpecialAbility, AbilityCooldown, false);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Nop"));
			}
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
	}
}