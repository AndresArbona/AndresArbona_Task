// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/Components/SkateMovementComponent.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "AndresArbona_Task/GAS/Attributes/AttibuteSet_Movement.h"

USkateMovementComponent::USkateMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void USkateMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(Owner))
	{
		ASC = ASI->GetAbilitySystemComponent();
	}

	if (ACharacter* Character = Cast<ACharacter>(Owner))
	{
		MovementComponent = Character->GetCharacterMovement();
	}

	MovementSet = ASC ? ASC->GetSet<UAttibuteSet_Movement>() : nullptr;
}

void USkateMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	if (!ASC || !MovementSet || !MovementComponent) return;

	// Pull attributes
	const float MaxSpeed = MovementSet->GetMaxSpeed();
	const float Accel = MovementSet->GetAcceleration();
	const float Fric = MovementSet->GetGroundFriction();
	const float Decel = MovementSet->GetBrakingDeceleration();
	const float AirCtl = MovementSet->GetAirControl();
	const float TurnLow = MovementSet->GetTurnRateLow();
	const float TurnHigh = MovementSet->GetTurnRateHigh();
	const float SpeedHi = MovementSet->GetSpeedHighAt();

	// Apply to movement
	MovementComponent->MaxWalkSpeed = MaxSpeed;
	MovementComponent->MaxAcceleration = Accel;
	MovementComponent->GroundFriction = Fric;
	MovementComponent->BrakingDecelerationWalking = Decel;
	MovementComponent->AirControl = AirCtl;
	MovementComponent->bOrientRotationToMovement = true;

	// Turn rate curve vs current speed
	const float Speed = GetSpeed2D();
	const float Alpha = FMath::Clamp(SpeedHi > 0.f ? (Speed / SpeedHi) : 0.f, 0.f, 1.f);
	const float TurnRate = FMath::Lerp(TurnLow, TurnHigh, Alpha);
	MovementComponent->RotationRate = FRotator(0.f, TurnRate, 0.f);
}

float USkateMovementComponent::GetSpeed2D() const
{
	if (ACharacter* Character = Cast<ACharacter>(GetOwner()))
	{
		return Character->GetVelocity().Size2D();
	}
	return 0.0f;
}



