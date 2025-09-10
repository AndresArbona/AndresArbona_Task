// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/Animator/PlayerAnimator.h"

#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemComponent.h"
#include "Animation/AnimMontage.h"
#include "AndresArbona_Task/GAS/SkateboardGameplayTagsList.h"

void UPlayerAnimator::NativeInitializeAnimation()
{
	OwnerChararacter = Cast<ACharacter>(TryGetPawnOwner());
	if (OwnerChararacter.IsValid())
	{
		if (IAbilitySystemInterface* ASI = Cast<IAbilitySystemInterface>(OwnerChararacter.Get()))
		{
			ASC = ASI->GetAbilitySystemComponent();
		}
		bPrevGrounded = true;
		bPrevPushing = false;
	}
}

void UPlayerAnimator::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!OwnerChararacter.IsValid()) { OwnerChararacter = Cast<ACharacter>(TryGetPawnOwner()); }
	if (OwnerChararacter.IsValid())
	{
		Speed = OwnerChararacter->GetVelocity().Size2D();
		if (const UCharacterMovementComponent* CharacterMovementComp = OwnerChararacter->GetCharacterMovement())
		{
			bGrounded = CharacterMovementComp->IsMovingOnGround();
		}
	}

	if (ASC.IsValid())
	{
		bPushing = ASC->HasMatchingGameplayTag(SkateTags::State_Pushing());
		bBraking = ASC->HasMatchingGameplayTag(SkateTags::State_Braking());
	}

	const bool bPushStarted = (bPushing && !bPrevPushing);
	const bool bJumpStarted = (!bGrounded && bPrevGrounded); // despegue
	const bool bLanded = (bGrounded && !bPrevGrounded); // aterrizaje

	if (bJumpStarted && JumpAnim)
	{
		PlayOneShot(JumpAnim);
	}
	else if (bPushStarted && PushAnim)
	{
		PlayOneShot(PushAnim);
	}
	else if (bLanded && LandAnim)
	{
		PlayOneShot(LandAnim);
	}

	EnsureBaseLoop();

	bPrevGrounded = bGrounded;
	bPrevPushing = bPushing;
}

void UPlayerAnimator::EnsureBaseLoop()
{
	UAnimSequence* Desired = (Speed >= SpeedForRoll && RollLoop) ? RollLoop : IdleLoop;
	if (!Desired) return;

	// Si cambió la base, reproducir nuevo loop
	if (Desired != CurrentBaseSequence)
	{
		UAnimMontage* Dyn = PlaySlotAnimationAsDynamicMontage(Desired, SlotName, BaseBlendIn, BaseBlendOut, 1.f, /*LoopCount*/0);
		if (Dyn)
		{
			CurrentBaseSequence = Desired;
		}
	}
	else
	{
		// Si por algún motivo no hay montage reproduciéndose (interrumpido), re-asegurar
		if (!IsAnyMontagePlaying())
		{
			PlaySlotAnimationAsDynamicMontage(Desired, SlotName, BaseBlendIn, BaseBlendOut, 1.f, 0);
		}
	}
}

void UPlayerAnimator::PlayOneShot(UAnimSequence* Sequence)
{
	if (!Sequence) return;
	PlaySlotAnimationAsDynamicMontage(Sequence, SlotName, OneShotBlendIn, OneShotBlendOut, 1.f, 1);
}
