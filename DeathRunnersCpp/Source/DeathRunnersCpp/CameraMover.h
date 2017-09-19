// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "CameraMover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DEATHRUNNERSCPP_API UCameraMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraMover();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		bool canMove = true;

private:
	UPROPERTY( EditAnywhere, Category = "Movement" )
	TArray<AActor*> actorsToMove;

	UPROPERTY( EditAnywhere, Category = "Movement" )
	float minSpeed;

	UPROPERTY( EditAnywhere, Category = "Movement" )
	float maxSpeed;

};
