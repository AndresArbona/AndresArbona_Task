// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AndresArbona_Task/GAS/Abilities/GA_SkateboardBase.h"
#include "GA_PushAbility.generated.h"

UCLASS()
class ANDRESARBONA_TASK_API UGA_PushAbility : public UGA_SkateboardBase
{
	GENERATED_BODY()
	
public:
	UGA_PushAbility();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle,
		const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo,
		const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditDefaultsOnly, Category = "Skate|GE")
	TSubclassOf<UGameplayEffect> GE_PushBuff;
	UPROPERTY(EditDefaultsOnly, Category = "Skate|GE")
	TSubclassOf<UGameplayEffect> GE_PushCooldown;
};
