// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/GAS/Abilities/GA_AwardScore.h"

#include "AndresArbona_Task/GAS/SkateboardGameplayTagsList.h"
#include "AndresArbona_Task/GAS/Attributes/AttributeSet_Score.h"
#include "AbilitySystemComponent.h"

UGA_AwardScore::UGA_AwardScore()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly; // el server decide el score

	FAbilityTriggerData Trigger;
	Trigger.TriggerTag = SkateTags::Event_ObstableCleared();
	Trigger.TriggerSource = EGameplayAbilityTriggerSource::GameplayEvent;
	AbilityTriggers.Add(Trigger);
}

void UGA_AwardScore::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
    if (!CommitAbility(Handle, ActorInfo, ActivationInfo)) {
        EndAbility(Handle, ActorInfo, ActivationInfo, /*replicate*/true, /*cancelled*/true);
        return;
    }

    UAbilitySystemComponent* ASC = ActorInfo ? ActorInfo->AbilitySystemComponent.Get() : nullptr;
    if (!ASC || !GE_AddScore) {
        EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
        return;
    }

    // Puntos: vienen en EventMagnitude del GameplayEvent
    const int32 Points = TriggerEventData ? (int32)TriggerEventData->EventMagnitude : 100;

    // Construir el spec y pasar la magnitud vía SetByCaller
    FGameplayEffectContextHandle ContextHelper = ASC->MakeEffectContext();
    FGameplayEffectSpecHandle SpecHelper = ASC->MakeOutgoingSpec(GE_AddScore, 1.f, ContextHelper);
    if (SpecHelper.IsValid())
    {
        SpecHelper.Data->SetSetByCallerMagnitude(SkateTags::Data_ScoreDelta(), (float)Points);
        ASC->ApplyGameplayEffectSpecToSelf(*SpecHelper.Data.Get());
        ASC->ExecuteGameplayCue(SkateTags::Cue_Score()); 
    }

    EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}