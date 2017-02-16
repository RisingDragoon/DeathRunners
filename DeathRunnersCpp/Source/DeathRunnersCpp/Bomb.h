// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "Bomb.generated.h"

/**
 * 
 */
UCLASS()
class DEATHRUNNERSCPP_API ABomb : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:
	ABomb();
	FTimerHandle Timer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		float Countdown = 3.0;

	UFUNCTION(BlueprintCallable, Category = "Funzioni")
	void StartTimer();

private:

	void Explode();

	FHitResult DestroyPlatformDown();
	
};
