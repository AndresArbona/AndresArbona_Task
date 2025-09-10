// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AndresArbona_Task/GAS/Abilities/GA_SkateboardBase.h"
#include "GA_BrakeAbility.generated.h"

/**
 * 
 */
UCLASS()
class ANDRESARBONA_TASK_API UGA_BrakeAbility : public UGA_SkateboardBase
{
	GENERATED_BODY()
	
public:
	UGA_BrakeAbility();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	UPROPERTY(EditDefaultsOnly, Category = "Skate|GE") TSubclassOf<UGameplayEffect> GE_Brake;
private:
	FActiveGameplayEffectHandle BrakeGEHandle;
};
