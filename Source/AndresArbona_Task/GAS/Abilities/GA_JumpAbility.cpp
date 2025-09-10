// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/GAS/Abilities/GA_JumpAbility.h"

#include "AndresArbona_Task/GAS/SkateboardGameplayTagsList.h"
#include "AbilitySystemComponent.h"
#include "AndresArbona_Task/GAS/Attributes/AttibuteSet_Movement.h"
#include "AndresArbona_Task/PlayerCharacter/PlayerCharacter.h"


UGA_JumpAbility::UGA_JumpAbility()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UGA_JumpAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	UAttibuteSet_Movement* MovementSet = GetMovementSet(ActorInfo);
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo) || !ASC || !MovementSet) { EndAbility(Handle, ActorInfo, ActivationInfo, true, true); return; }

	const float Speed = GetSpeed2D(ActorInfo);
	if (!IsGrounded(ActorInfo) || Speed < MovementSet->GetMinJumpSpeed()) { EndAbility(Handle, ActorInfo, ActivationInfo, true, true); return; }

	// Impulse up
	if (APlayerCharacter* PlayerRef = GetSkater(ActorInfo))
	{
		PlayerRef->LaunchCharacter(FVector(0, 0, MovementSet->GetJumpImpulse()), false, true);
	}
	ASC->ExecuteGameplayCue(SkateTags::Cue_Jump());
	ASC->AddLooseGameplayTag(SkateTags::State_Airbone());

	if (GE_AirControl)
	{
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GE_AirControl, 1.f, ContextHandle);
		if (SpecHandle.IsValid()) { ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get()); }
	}

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}