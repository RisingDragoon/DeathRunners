// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "CameraMover.h"

UCameraMover::UCameraMover()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UCameraMover::BeginPlay()
{
	Super::BeginPlay();
	
	for ( int i = 0; i < 4; i++ )
	{
		ACharacter* character = UGameplayStatics::GetPlayerCharacter( GetWorld(), i );

		if ( character != nullptr )
		{
			characters.Add( character );
			UE_LOG( LogTemp, Warning, TEXT( "Character %d detected and added to camera mover array." ), i );
		}
	}
}

void UCameraMover::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	float averageZ = 0;
	
	for ( auto item : characters )
	{
		if (item)
		{
			averageZ += item->GetActorLocation().Z;
		}
	}

	averageZ /= characters.Num();

	float speedFactor = (( averageZ - GetOwner()->GetActorLocation().Z ) / 1080.0 ) + 0.5;
	float speed = FMath::Lerp( minSpeed, maxSpeed, speedFactor );

	FVector offset = FVector( 0.0, 0.0, speed ) * DeltaTime;

	for ( auto item : actorsToMove )
	{
		if (item)
		{
			item->AddActorWorldOffset( offset, false );
		}
	}

	GetOwner()->AddActorWorldOffset( offset, false );
}
