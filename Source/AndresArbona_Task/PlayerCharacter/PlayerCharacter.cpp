// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/PlayerCharacter/PlayerCharacter.h"

#include "AndresArbona_Task/GAS/SkateboardAbilitySystemComponent.h"
#include "AndresArbona_Task/GAS/Attributes/AttibuteSet_Movement.h"
#include "AndresArbona_Task/GAS/Attributes/AttributeSet_Score.h"
#include "AndresArbona_Task/Components/SkateMovementComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AndresArbona_Task/GAS/Enum/ESkateboardInputs.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<USkateboardAbilitySystemComponent>(TEXT("ASC"));

	SkateMovementComponent = CreateDefaultSubobject<USkateMovementComponent>(TEXT("SkateMovementComponent"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.f; 
	SpringArm->bUsePawnControlRotation = true; 
	SpringArm->bEnableCameraLag = true; 
	SpringArm->CameraLagSpeed = 10.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	SkateStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkateMesh"));
	SkateStaticMesh->SetupAttachment(GetMesh());

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const { return ASC; }


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeAttributes();
	GiveDefaultAbilities();

	if (ASC)
	{
#if 1
		MovementSet = ASC->GetSet<UAttibuteSet_Movement>();
#else
		MovementSet = Cast<UAttibuteSet_Movement>(ASC->GetAttributeSet(UAttibuteSet_Movement::StaticClass()));
#endif
	}
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APlayerCharacter::IsGrounded() const
{
	return GetCharacterMovement() && GetCharacterMovement()->IsMovingOnGround();
}

float APlayerCharacter::GetSpeed2D() const
{
	return GetVelocity().Size2D();
}

void APlayerCharacter::ProcessMoveInput(const FVector2D& Axis, float DeltaSeconds)
{

	const float Throttle = FMath::Clamp(Axis.Y, 0.f, 1.f);
	const float Steer = FMath::Clamp(Axis.X, -1.f, 1.f); 


	const float Speed = GetSpeed2D();

	float TurnLow = 90.f, TurnHigh = 45.f, SpeedHighAt = 1200.f;
	if (MovementSet)
	{
		TurnLow = MovementSet->GetTurnRateLow();
		TurnHigh = MovementSet->GetTurnRateHigh();
		SpeedHighAt = MovementSet->GetSpeedHighAt();
	}

	const float Alpha = FMath::Clamp(SpeedHighAt > 0.f ? (Speed / SpeedHighAt) : 0.f, 0.f, 1.f);
	const float TurnRate = FMath::Lerp(TurnLow, TurnHigh, Alpha);
	const float SteerGain = FMath::GetMappedRangeValueClamped(FVector2D(0.f, 200.f), FVector2D(0.25f, 1.f), Speed);
	const float YawDelta = Steer * TurnRate * SteerGain * DeltaSeconds;

	if (FMath::Abs(YawDelta) > KINDA_SMALL_NUMBER)
	{
		AddActorWorldRotation(FRotator(0.f, YawDelta, 0.f));
	}

	if (Throttle > 0.f)
	{
		AddMovementInput(GetActorForwardVector(), Throttle);
	}
}

void APlayerCharacter::ClearMoveInput()
{
	// no cacheamos nada
}

void APlayerCharacter::InitializeAttributes()
{
	if (ASC && GE_StartupAttributes)
	{
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GE_StartupAttributes, 1.f, ContextHandle);
		if (SpecHandle.IsValid()) 
		{ 
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get()); 
		}
	}
}

void APlayerCharacter::GiveDefaultAbilities()
{
	if (!ASC || !HasAuthority()) return;
	
	if (GA_PushClass)
	{
		PushHandle = ASC->GiveAbility(
			FGameplayAbilitySpec(GA_PushClass, 1,
				static_cast<int32>(ESkateboardInputs::Push), this));
	}
	if (GA_BrakeClass)
	{
		BrakeHandle = ASC->GiveAbility(
			FGameplayAbilitySpec(GA_BrakeClass, 1,
				static_cast<int32>(ESkateboardInputs::Brake), this));
	}
	if (GA_JumpClass)
	{
		JumpHandle = ASC->GiveAbility(
			FGameplayAbilitySpec(GA_JumpClass, 1,
				static_cast<int32>(ESkateboardInputs::Jump), this));
	}
}