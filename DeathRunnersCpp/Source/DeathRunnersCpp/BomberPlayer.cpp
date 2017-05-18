// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "BomberPlayer.h"
#include "Bomb.h"


void ABomberPlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	UE_LOG(LogTemp, Warning, TEXT("input setup"));
	Super::SetupPlayerInputComponent(playerInputComponent);
	playerInputComponent->BindAction("Bomb", IE_Released, this, &ABomberPlayer::SpecialAbility);
	//SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("SpawnPoint"));
	//tatic ConstructorHelpers::FObjectFinder<UBlueprint> ItemBlueprint(TEXT("Blueprint'/Game/Items/Blueprints/BP_ItemTest.BP_ItemTest'"));
}

void ABomberPlayer::SpecialAbility()
{
	if (SpecialAbilityIsReady)
	{
		UWorld* const World = GetWorld();
		if (World) 
		{
			//FActorSpawnParameters SpawnParams;
			//SpawnParams.Instigator = this;
			//FVector location = SpawnPoint
			//World->SpawnActor<ABomb>(BombBlueprint, location, FRotator::ZeroRotator, SpawnParams);
		}
		StartAnimation(PlayerAnimation::Skill);
		UE_LOG(LogTemp, Warning, TEXT("Usata bomba"));
		SpecialAbilityIsReady = false;
		GetWorld()->GetTimerManager().SetTimer(TimerSpecialAbility, this, &ABasePlayer::EnableSpecialAbility, AbilityCooldown, false);
	}
}