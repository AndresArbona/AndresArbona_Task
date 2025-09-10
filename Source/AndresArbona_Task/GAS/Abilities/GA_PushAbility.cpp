// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/GAS/Abilities/GA_PushAbility.h"

#include "AndresArbona_Task/GAS/SkateboardGameplayTagsList.h"
#include "AbilitySystemComponent.h"

UGA_PushAbility::UGA_PushAbility() 
{
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::LocalPredicted; 
}

void UGA_PushAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) { EndAbility(Handle, ActorInfo, ActivationInfo, true, true); return; }
	UAbilitySystemComponent* ASC = ActorInfo->AbilitySystemComponent.Get();
	
	if (!ASC || !IsGrounded(ActorInfo) || ASC->HasMatchingGameplayTag(SkateTags::Cooldown_Push()))
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true); return;
	}
	if (GE_PushBuff)
	{
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(GE_PushBuff, 1.f, ContextHandle);
		if (SpecHandle.IsValid()) { ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get()); }
	}
	ASC->ExecuteGameplayCue(SkateTags::Cue_Push());

	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
