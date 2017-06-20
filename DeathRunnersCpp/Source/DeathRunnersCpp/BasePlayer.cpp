// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathRunnersCpp.h"
#include "BasePlayer.h"
#include "DeathRunnersCppGameMode.h"
#include "PaperFlipbookComponent.h"
#include "Components/TextRenderComponent.h"
#include "BasePlatform.h"
#include "GunPlayer.h"
#include <string>


ABasePlayer::ABasePlayer()
{
	GetSprite()->SetIsReplicated(true);
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	TimerSpecialAbility = FTimerHandle();
	TimerFalling = FTimerHandle();
	TimerEndAnimation = FTimerHandle();
	TimerGainControl = FTimerHandle();

	UCapsuleComponent* capsule = GetCapsuleComponent();
	capsule->OnComponentBeginOverlap.__Internal_AddDynamic(this, &ABasePlayer::SetPlayerToSmash, FName("SetPlayerToSmash"));
	capsule->OnComponentEndOverlap.__Internal_AddDynamic(this, &ABasePlayer::ResetPlayerToSmash, FName("ResetPlayerToSmash"));
	SoundComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("SoundComponent"));

	UCameraComponent* camera = (UCameraComponent*)GetComponentByClass(UCameraComponent::StaticClass());
	if (camera)
	{
		UE_LOG(LogTemp, Warning, TEXT("HA UNA CAMERA"));
	}

	//static ConstructorHelpers::FObjectFinder<UParticleSystem> PS(TEXT("ParticleSystem'/Game/StarterContent/Particles/P_Fire.P_Fire'"));
	//ParticleSystemCharging = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("MyPSC"));
	//SoundWave'/Game/Sounds/dr_grab.dr_grab'
	//ParticleSystemCharging->SetTemplate(PS.Object);
	//ParticleSystemCharging->Activate();
	//ParticleSystemCharging->SetActive(false);
}

void ABasePlayer::SetupPlayerInputComponent(class UInputComponent* playerInputComponent)
{
	playerInputComponent->BindAxis("MoveRightOrLeft", this, &ABasePlayer::MoveRightOrLeft);
	playerInputComponent->BindAction("Jump", IE_Pressed, this, &ABasePlayer::Jump);
	playerInputComponent->BindAction("ChargeSmash", IE_Pressed, this, &ABasePlayer::ChargeSmash);
	playerInputComponent->BindAction("ChargeSmash", IE_Released, this, &ABasePlayer::StopCharging);
	playerInputComponent->BindAction("Smash", IE_Pressed, this, &ABasePlayer::ThrowSmash);
}

void ABasePlayer::Jump()
{
	if (IsCharging)
	{
		StopCharging();
	}
	Super::Jump();
	SetSounds(PlayerAnimation::JumpStart);
}

void ABasePlayer::SetSounds(PlayerAnimation animation)
{
	switch (animation)
	{
	case PlayerAnimation::Smash:
		if (SmashAudio)
		{
			SoundComponent->SetSound(SmashAudio);
		}
		break;
	case PlayerAnimation::Stun:
		if (StunAudio)
		{
			SoundComponent->SetSound(StunAudio);
		}
		break;
	case PlayerAnimation::JumpStart:
		if (JumpAudio)
		{
			SoundComponent->SetSound(JumpAudio);
		}
		break;
	case PlayerAnimation::JumpEnd:
		break;
	case PlayerAnimation::RunStart:
		break;
	case PlayerAnimation::RunEnd:
		break;
	case PlayerAnimation::RunChangeDirection:
		break;
	case PlayerAnimation::JumpChangeDirection:
		break;
	case PlayerAnimation::Die:
		break;
	case PlayerAnimation::DropChangeDirection:
		break;
	case PlayerAnimation::Skill:
		if (SpecialAbilityAudio)
		{
			SoundComponent->SetSound(SpecialAbilityAudio);
		}
		break;
	default:
		break;
	}
	//PlaySound();
}

void ABasePlayer::ChargeSmash()
{
	//ParticleSystemCharging->SetActive(true);
	//ParticleSystemCharging->Activate();
	UE_LOG(LogTemp, Warning, TEXT("ChargeSmash"));
	if (!IsJumping && !IsFalling)
	{
		UE_LOG(LogTemp, Warning, TEXT("ChargeSmash Partito"));
		IsCharging = true;
	}
}

void ABasePlayer::StopCharging()
{
	UE_LOG(LogTemp, Warning, TEXT("ChargeSmash Terminato"));
	IsCharging = false;
}

void ABasePlayer::MoveRightOrLeft(float value)
{
	UpdateCharacter();
	if (value == 0)
	{
		return;
	}
	if (!IsOutOfControl)
	{
		if (value > 0  && value < DeadZoneUp)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Valore %f "), value);
			value = DeadZoneUp;
		}
		else if (value < 0 && value > DeadZoneDown)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Valore %f "), value);
			value = DeadZoneDown;
		}
		if(value>0)
		{
			if (!IsFaceRight)
			{
				IsFaceRight = true;
				//UE_LOG(LogTemp, Warning, TEXT("IsFaceRight = true"));
			}
		}
		else if (value<0)
		{
			if (IsFaceRight)
			{
				IsFaceRight = false;
				//UE_LOG(LogTemp, Warning, TEXT("IsFaceRight = false"));
			}
		}

		if (IsCharging && !IsJumping)
		{
			//UE_LOG(LogTemp, Warning, TEXT("Carico e mi muovo di meta"));
			AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value / 2);
		}
		else
		{
			AddMovementInput(FVector(1.0f, 0.0f, 0.0f), value);
		}
	}
}

void ABasePlayer::SetAnimationIdleNoHand(UPaperFlipbook * NoHand)
{
	HasNoHand = true;
	NoHandAnimation = NoHand;
}

void ABasePlayer::ThrowSmash()
{
	UE_LOG(LogTemp, Warning, TEXT("ThrowSmash"));
	if (IsJumping)
	{
		//StopCharging();
		StartAnimation(PlayerAnimation::Smash);
		SetSounds(PlayerAnimation::Smash);

		if (CanSmash && PlayerToSmash != nullptr && !IsFalling && !IsOutOfControl)
		{
			if (PlayerToSmash->IsJumping)
			{
				UE_LOG(LogTemp, Warning, TEXT("Potenza pugno : SmashForce= %f "), SmashForce);
				//if (SmashForce < BaseSmashForce)
				//{
				//	//Applica la forza minima
				//	SmashForce = BaseSmashForce;
				//}
				PlayerToSmash->AppliedForce = SmashForce;
				PlayerToSmash->StartFalling();
			}
		}
		SmashForce = BaseSmashForce;
	}
}

void ABasePlayer::ReceiveShot()
{
	//Metto la AppliedForce sempre minore del livello della forza così quando vieni colpito dallo sparo non è un pugno caricato
	AppliedForce = SmashForceLevel - 1;
	StartFalling();
}

void ABasePlayer::EnableSpecialAbility()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Abilita Pronta"), *this->GetName());
	SpecialAbilityIsReady = true;
}

void ABasePlayer::StartFalling()
{
	IsOutOfControl = true;
	IsFalling = true;
	StartAnimation(PlayerAnimation::Hit);
	if (AppliedForce > SmashForceLevel)
	{
		//Pugno caricato
		UE_LOG(LogTemp, Warning, TEXT("PUGNO CARICATO"));
		if (GetCapsuleComponent())
		{
			UE_LOG(LogTemp, Warning, TEXT("Stato Collisioni Falling"));
			GetCapsuleComponent()->SetCollisionProfileName(TEXT("Falling"));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Errore - Capsule component del player e' null"));
		}
		LaunchCharacter(FVector(0.0f, 0.0f, -AppliedForce), true, true);
	}
	else
	{
		//Pugno base
		UE_LOG(LogTemp, Warning, TEXT("PUGNO BASE"));
		LaunchCharacter(FVector(0.0f, 0.0f, -BaseSmashForce), true, true);
	}
	GetWorld()->GetTimerManager().SetTimer(TimerFalling, this, &ABasePlayer::StopFalling, FallingTimeRate, false);
}

void ABasePlayer::StopFalling()
{
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
	UE_LOG(LogTemp, Warning, TEXT("Stop falling"));
	IsOutOfControl = false;
	IsFalling = false;
}

void ABasePlayer::Spike()
{
	UE_LOG(LogTemp, Warning, TEXT("Spikato"));
	StartAnimation(PlayerAnimation::Knock);
	int min = FMath::RandRange(-SpikeForce, -10);
	int max = FMath::RandRange(10, SpikeForce);

	int randomic = FMath::RandRange(min, max);
	//float dir = (randomic) ? 10.0 : -10.0;
	FVector LaunchVelocity = FVector(randomic, 0.0, 1.0) * SpikeLaunchSpeed;
	LaunchCharacter(LaunchVelocity, true, true);
	//LoseControl();
}

void ABasePlayer::StartAnimation(PlayerAnimation animazione)
{
	float timeOfAnimation = 0;

	switch (animazione)
	{
	case PlayerAnimation::Smash:
		if (Smash)
		{
			timeOfAnimation = Smash->GetTotalDuration();
		}
		break;
	case PlayerAnimation::Stun:
		if (Stun)
		{
			timeOfAnimation = Stun->GetTotalDuration();
		}
		break;
	case PlayerAnimation::JumpStart:
		if (JumpStart)
		{
			timeOfAnimation = JumpStart->GetTotalDuration();
		}
		break;
	case PlayerAnimation::JumpEnd:
		if (JumpEnd)
		{
			timeOfAnimation = JumpEnd->GetTotalDuration();
		}
		break;
	case PlayerAnimation::RunStart:
		if (RunStart)
		{
			timeOfAnimation = RunStart->GetTotalDuration();
		}
		break;
	case PlayerAnimation::RunEnd:
		if (RunEnd)
		{
			timeOfAnimation = RunEnd->GetTotalDuration();
		}
		break;
	case PlayerAnimation::RunChangeDirection:
		if (RunChangeDirection)
		{
			timeOfAnimation = RunChangeDirection->GetTotalDuration();
		}
		break;
	case PlayerAnimation::JumpChangeDirection:
		if (JumpChangeDirection)
		{
			timeOfAnimation = JumpChangeDirection->GetTotalDuration();
		}
		break;
	case PlayerAnimation::Die:
		if (Die)
		{
			timeOfAnimation = Die->GetTotalDuration();
		}
		break;
	case PlayerAnimation::DropChangeDirection:
		if (DropChangeDirection)
		{
			timeOfAnimation = DropChangeDirection->GetTotalDuration();
		}
		break;
	case PlayerAnimation::Hit:
		if (Hit)
		{
			timeOfAnimation = Hit->GetTotalDuration();
			break;
		}
	case PlayerAnimation::Skill:
		if (Skill)
		{
			timeOfAnimation = Skill->GetTotalDuration();
			break;
		}
	case PlayerAnimation::Knock:
		if (Knock)
		{
			timeOfAnimation = Knock->GetTotalDuration();
			break;
		}
	case PlayerAnimation::Smaterialize:
		if (SmaterializeAnimation)
		{
			timeOfAnimation = SmaterializeAnimation->GetTotalDuration();
			break;
		}
	case PlayerAnimation::Materialize:
		if (MaterializeAnimation)
		{
			timeOfAnimation = MaterializeAnimation->GetTotalDuration();
			break;
		}
	case PlayerAnimation::Idle:
		if (Idle)
		{
			timeOfAnimation = Idle->GetTotalDuration();
			break;
		}
	case PlayerAnimation::Running:
		if (Running)
		{
			timeOfAnimation = Running->GetTotalDuration();
			break;
		}
	case PlayerAnimation::Drop:
		if (Dropping)
		{
			timeOfAnimation = Dropping->GetTotalDuration();
			break;
		}
	case PlayerAnimation::Falling:
		if (Falling)
		{
			timeOfAnimation = Falling->GetTotalDuration();
			break;
		}
	case PlayerAnimation::AirPuke:
		if (AirPuke)
		{
			timeOfAnimation = AirPuke->GetTotalDuration();
			break;
		}
	}
	if (SelectedAnimation != animazione)
	{
		SelectedAnimation = animazione;
		UE_LOG(LogTemp, Warning, TEXT("Durata animazione %d"), timeOfAnimation);
		UE_LOG(LogTemp, Warning, TEXT("StartAnimation"));
		GetWorld()->GetTimerManager().SetTimer(TimerEndAnimation, this, &ABasePlayer::EndAnimation, timeOfAnimation, false);
	}
}

void ABasePlayer::EndAnimation()
{
	UE_LOG(LogTemp, Warning, TEXT("EndAnimation"));
	if (SelectedAnimation == PlayerAnimation::Smaterialize)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Teleport"));
		SetActorLocation(LocationToTeleport);
		StartAnimation(PlayerAnimation::Materialize);
	}
	else if (SelectedAnimation == PlayerAnimation::Materialize)
	{
		//UE_LOG(LogTemp, Warning, TEXT("materializza"));
		IsOutOfControl = false;
		SelectedAnimation = PlayerAnimation::Nothing;
	}
	else if (SelectedAnimation == PlayerAnimation::Stun)
	{
		IsOutOfControl = false;
		SelectedAnimation = PlayerAnimation::Nothing;
	}
	else
	{
		SelectedAnimation = PlayerAnimation::Nothing;
	}
}

void ABasePlayer::SpecialAbility()
{
}

void ABasePlayer::PlaySound()
{
	//SoundComponent->Play(0.0);
}

void ABasePlayer::Suicide()
{
	ADeathRunnersCppGameMode* gameMode = (ADeathRunnersCppGameMode*) GetWorld()->GetAuthGameMode();
	gameMode->RemovePlayer( this );
	Destroy();
}

void ABasePlayer::SetPlayerToSmash(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//UE_LOG(LogTemp, Warning, TEXT("SetPlayerToSmash"));
	//ABasePlayer* classe = OtherActor->GetActorClass();
	ABasePlayer* player = (ABasePlayer*) (OtherActor);
	if (player != nullptr)
	{
		FString nome = player->GetName();
		if (nome.Contains(FString("Player")))
		{
			//UE_LOG(LogTemp, Warning, TEXT("Settato playertosmash %s"), *nome);
			CanSmash = true;
			PlayerToSmash = player;
		}
		else
		{
			//UE_LOG(LogTemp, Warning, TEXT("null playertosmash"));
			PlayerToSmash = nullptr;
		}
	}
	else
	{
		//UE_LOG(LogTemp, Warning, TEXT("null playertosmash"));
		PlayerToSmash = nullptr;
	}
}

void ABasePlayer::ResetPlayerToSmash(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTemp, Warning, TEXT("ResetPlayerToSmash"));
	ABasePlayer* player = static_cast<ABasePlayer*>(OtherActor);
	if (player)
	{
		//UE_LOG(LogTemp, Warning, TEXT("CanSmash = false;"));
		CanSmash = false;
		PlayerToSmash = nullptr;
	}
}

void ABasePlayer::GetFlipbookByAnimation(PlayerAnimation animation)
{
	switch (animation)
	{
	case PlayerAnimation::Smash:
		if (Smash)
		{
			SelectedFlipbook = Smash;
		}
		break;
	case PlayerAnimation::Stun:
		if (Stun)
		{
			SelectedFlipbook = Stun;
		}
		break;
	case PlayerAnimation::JumpStart:
		if (JumpStart)
		{
			SelectedFlipbook = JumpStart;
		}
		break;
	case PlayerAnimation::JumpEnd:
		if (JumpEnd)
		{
			SelectedFlipbook = JumpEnd;
		}
		break;
	case PlayerAnimation::RunStart:
		if (RunStart)
		{
			SelectedFlipbook = RunStart;
		}
		break;
	case PlayerAnimation::RunEnd:
		if (RunEnd)
		{
			SelectedFlipbook = RunEnd;
		}
		break;
	case PlayerAnimation::RunChangeDirection:
		if (RunChangeDirection)
		{
			SelectedFlipbook = RunChangeDirection;
		}
		break;
	case PlayerAnimation::JumpChangeDirection:
		if (JumpChangeDirection)
		{
			SelectedFlipbook = JumpChangeDirection;
		}
		break;
	case PlayerAnimation::Die:
		if (Die)
		{
			SelectedFlipbook = Die;
		}
		break;
	case PlayerAnimation::DropChangeDirection:
		if (DropChangeDirection)
		{
			SelectedFlipbook = DropChangeDirection;
		}
		break;
	case PlayerAnimation::Skill:
		if (Skill)
		{
			SelectedFlipbook = Skill;
		}
		break;
	case PlayerAnimation::Knock:
		if (Knock)
		{
			SelectedFlipbook = Knock;
		}
		break;
	case PlayerAnimation::Hit:
		if (Hit)
		{
			SelectedFlipbook = Hit;
		}
		break;
	case PlayerAnimation::Smaterialize:
		if (SmaterializeAnimation)
		{
			SelectedFlipbook = SmaterializeAnimation;
		}
		break;
	case PlayerAnimation::Materialize:
		if (MaterializeAnimation)
		{
			SelectedFlipbook = MaterializeAnimation;
		}
		break;
	case PlayerAnimation::NoHand:
		if (NoHandAnimation)
		{
			SelectedFlipbook = NoHandAnimation;
		}
		break;
	case PlayerAnimation::AirPuke:
		if (AirPuke)
		{
			SelectedFlipbook = AirPuke;
		}
		break;
	}
}

void ABasePlayer::UpdateAnimation()
{
	const FVector PlayerVelocity = GetVelocity();

	UPaperFlipbook* DesiredAnimation;
	if (SelectedAnimation != PlayerAnimation::Nothing)
	{
		GetFlipbookByAnimation(SelectedAnimation);
		if (SelectedFlipbook)
		{
			DesiredAnimation = SelectedFlipbook;
		}
		else
		{
			DesiredAnimation = Idle;
		}
	}
	else if (HasNoHand)
	{
		DesiredAnimation = NoHandAnimation;
	}
	else if (IsFalling)
	{
		DesiredAnimation = Falling;
	}
	else if (PlayerVelocity.Z > 0.0f)
	{
		DesiredAnimation = Jumping;
	}
	else if (PlayerVelocity.Z < 0.0f)
	{
		DesiredAnimation = Dropping;
	}
	else if (PlayerVelocity.X != 0.0f)
	{
		DesiredAnimation = Running;
	}
	else
	{
		DesiredAnimation = Idle;
	}
	if (GetSprite()->GetFlipbook() != DesiredAnimation)
	{
		GetSprite()->SetFlipbook(DesiredAnimation);
	}
}

void ABasePlayer::Tick(float deltaSeconds)
{
	Super::Tick(deltaSeconds);
	UpdateCharacter();
	//ParticleSystemCharging->SetRelativeLocation(GetActorLocation());
	IsJumping = GetVelocity().Z != 0.0f;
	if (IsCharging && SmashForce < MaxSmashForce)
	{
		SmashForce += SmashChargeSpeed;
		UE_LOG(LogTemp, Warning, TEXT("Potenza pugno : SmashForce= %f "), SmashForce);
	}
}

void ABasePlayer::BeginPlay()
{
	Super::BeginPlay();
	//ParticleSystemCharging->SetActive(false);

	ADeathRunnersCppGameMode* gameMode = (ADeathRunnersCppGameMode*)GetWorld()->GetAuthGameMode();
	gameMode->AddPlayer( this );
}

void ABasePlayer::UpdateCharacter()
{
	UpdateAnimation();
	const FVector PlayerVelocity = GetVelocity();
	float TravelDirection = PlayerVelocity.X;
	if (Controller != nullptr)
	{
		//Ruota il Player
		if (TravelDirection < 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0, 180.0f, 0.0f));
		}
		else if (TravelDirection > 0.0f)
		{
			Controller->SetControlRotation(FRotator(0.0f, 0.0f, 0.0f));
		}
	}
	if (PlayerVelocity.Z > 0.0f)
	{
		if (GetCapsuleComponent()->GetCollisionProfileName() != "Jumping")
		{
			//UE_LOG(LogTemp, Warning, TEXT("Jumping"));
			GetCapsuleComponent()->SetCollisionProfileName(TEXT("Jumping"));
		}

	}
	else if (!IsFalling)
	{
		TArray<AActor*> overlappingPlatforms;
		GetOverlappingActors(overlappingPlatforms, TSubclassOf<ABasePlatform>());
		
		if (overlappingPlatforms.Num() == 0)
		{
			if (GetCapsuleComponent()->GetCollisionProfileName() != "Pawn")
			{
				//UE_LOG(LogTemp, Warning, TEXT("SET pawn"));
				GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
			}
		}
	}
	else if (IsFalling)
	{
		if (AppliedForce <= SmashForceLevel)
		{
			if (GetCapsuleComponent()->GetCollisionProfileName() != "Pawn")
			{
				//UE_LOG(LogTemp, Warning, TEXT("Pawn da falling dopo pugno base"));
				GetCapsuleComponent()->SetCollisionProfileName(TEXT("Pawn"));
			}
		}
	}
}

void ABasePlayer::RegainControl()
{
	UE_LOG(LogTemp, Warning, TEXT("%s RegainControl"), *GetName());
	IsOutOfControl = false;
	StopFalling();
}

void ABasePlayer::LoseControl()
{
	UE_LOG(LogTemp, Warning, TEXT("%s Loses control"), *GetName());
	IsOutOfControl = true;
	StartAnimation(PlayerAnimation::Stun);
	SetSounds(PlayerAnimation::Stun);
	GetWorld()->GetTimerManager().SetTimer(TimerGainControl, this, &ABasePlayer::RegainControl, FallingTimeRate, false);
}
