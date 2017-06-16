// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "BasePlatform.h"
#include "BasePlayer.h"

// Sets default values
ABasePlatform::ABasePlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	UPaperSpriteComponent* sprite = GetRenderComponent();
	sprite->OnComponentHit.AddDynamic( this, &ABasePlatform::OnHit );
}

// Called when the game starts or when spawned
void ABasePlatform::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABasePlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABasePlatform::OnHit( UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit )
{
	ABasePlayer* HitCharacter = Cast<ABasePlayer>( OtherActor );

	if ( HitCharacter != NULL && HitCharacter->GetActorLocation().Z > GetActorLocation().Z + 32.0 )
	{
		if (HitCharacter->IsFalling)
		{
			UE_LOG(LogTemp, Warning, TEXT("ha sbattuto qundi Lose control"));

			HitCharacter->LoseControl();
		}

		if ( Type == EPlatformType::Spikes )
		{
			HitCharacter->Spike();
			/*float dir = HitCharacter->GetActorLocation().X > GetActorLocation().X ? 1.0 : -1.0;
			FVector LaunchVelocity = FVector( dir, 0.0, 1.0 ) * LaunchSpeed;
			HitCharacter->LaunchCharacter( LaunchVelocity, true, true );
			HitCharacter->LoseControl();*/
		}
		else if ( Type == EPlatformType::Bouncer )
		{
			FVector LaunchVelocity = FVector( 0.0, 0.0, LaunchSpeed );
			HitCharacter->LaunchCharacter( LaunchVelocity, false, false );
		}
	}
}
