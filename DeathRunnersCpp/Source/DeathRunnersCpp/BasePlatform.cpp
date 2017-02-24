// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "BasePlatform.h"

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
	ACharacter* HitCharacter = Cast<ACharacter>( OtherActor );

	if ( HitCharacter != NULL && HitCharacter->GetActorLocation().Z > GetActorLocation().Z + 32.0 )
	{
		if ( Type == EPlatformType::Spikes )
		{
			// UE_LOG( LogTemp, Warning, TEXT( "Someone just got spiked!" ) );
			FVector Direction = FMath::VRand();
			FVector LaunchVelocity = FVector( Direction.X, 0.0, Direction.Z ) * LaunchSpeed;
			HitCharacter->LaunchCharacter( LaunchVelocity, false, false );
		}
		else if ( Type == EPlatformType::Bouncer )
		{
			FVector LaunchVelocity = FVector( 0.0, 0.0, LaunchSpeed );
			HitCharacter->LaunchCharacter( LaunchVelocity, false, false );
		}
	}
}
