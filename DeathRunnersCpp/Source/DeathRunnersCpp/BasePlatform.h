// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PaperSpriteActor.h"
#include "BasePlatform.generated.h"

UENUM( BlueprintType )
enum class EPlatformType : uint8
{
	Standard,
	Spikes,
	Bouncer
};

UCLASS()
class DEATHRUNNERSCPP_API ABasePlatform : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABasePlatform();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Platform)
		bool IsDestructible = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Platform)
		EPlatformType Type;
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = Platform )
		float LaunchSpeed;

	UFUNCTION()
		void OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
};
