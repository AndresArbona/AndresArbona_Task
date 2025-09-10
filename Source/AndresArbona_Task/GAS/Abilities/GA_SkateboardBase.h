// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GA_SkateboardBase.generated.h"

UCLASS()
class ANDRESARBONA_TASK_API UGA_SkateboardBase : public UGameplayAbility
{
	GENERATED_BODY()
	

public:
	UGA_SkateboardBase();

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo, 
		const FGameplayEventData* TriggerEventData) override;
		
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, 
		const FGameplayAbilityActorInfo* ActorInfo, 
		const FGameplayAbilityActivationInfo ActivationInfo,
		bool bReplicateEndAbility, 
		bool bWasCancelled) override;

protected:
	TObjectPtr<class APlayerCharacter> GetSkater(const FGameplayAbilityActorInfo* ActorInfo) const;
	TObjectPtr<class UCharacterMovementComponent> GetMovementComponent(const FGameplayAbilityActorInfo* ActorInfo) const;
	TObjectPtr<const class UAttibuteSet_Movement> GetMovementSet(const FGameplayAbilityActorInfo* ActorInfo) const;


	bool IsGrounded(const FGameplayAbilityActorInfo* ActorInfo) const;
	float GetSpeed2D(const FGameplayAbilityActorInfo* ActorInfo) const;
};
