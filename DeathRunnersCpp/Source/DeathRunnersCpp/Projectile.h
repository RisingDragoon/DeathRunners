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
		FVector DirectionToGo = FVector(0,0,0);

	void SetDirectionToGo(FVector direction, FString playerName);

	float Speed = 5;

	UFUNCTION()
		void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	//FString PlayerName;
	bool Move=false;
};
