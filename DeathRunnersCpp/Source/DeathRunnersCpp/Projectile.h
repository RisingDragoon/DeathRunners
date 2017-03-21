// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "Projectile.generated.h"

/**
 * 
 */
//UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
UCLASS()
class DEATHRUNNERSCPP_API AProjectile : public APaperSpriteActor
{
	GENERATED_BODY()
	
public: 
	AProjectile();

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Modificabili)
		FVector DirectionToGo = FVector();

	void SetDirectionToGo(FVector direction);
	float Speed = 5;

private:
	bool Move=false;
	
};
