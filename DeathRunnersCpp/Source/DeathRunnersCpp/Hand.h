// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "Hand.generated.h"

class AGrapplePlayer;
/**
 * 
 */

UCLASS()
class DEATHRUNNERSCPP_API AHand : public APaperSpriteActor
{
	GENERATED_BODY()
public:
	AHand();

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		FVector DirectionToGo = FVector(0, 0, 0);

	void SetDirectionToGo(FVector direction, AGrapplePlayer* player);

	float Speed = 5;

	AGrapplePlayer* GrapplePlayer = nullptr;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	bool Move = false;
};
