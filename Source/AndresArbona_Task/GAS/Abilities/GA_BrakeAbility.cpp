// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/GAS/Abilities/GA_BrakeAbility.h"

#include "AndresArbona_Task/GAS/SkateboardGameplayTagsList.h"
#include "AbilitySystemComponent.h"

UGA_BrakeAbility::UGA_BrakeAbility()
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted;
}

void UGA_BrakeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) { EndAbility(Handle, ActorInfo, ActivationInfo, true, true); return; }
	if (UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get())
	{
		if (GE_Brake)
		{
			FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GE_Brake, 1.f, ContextHandle);
			if (SpecHandle.IsValid()) { BrakeGEHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get()); }
		}
		ASC->ExecuteGameplayCue(SkateTags::Cue_Brake());
	}
}

void UGA_BrakeAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get())
	{
		if (BrakeGEHandle.IsValid()) { ASC->RemoveActiveGameplayEffect(BrakeGEHandle); }
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
