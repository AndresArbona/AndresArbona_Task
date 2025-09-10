// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/GAS/Abilities/GA_SkateboardBase.h"

#include "GameFramework/CharacterMovementComponent.h"
#include "AndresArbona_Task/PlayerCharacter/PlayerCharacter.h"
#include "AndresArbona_Task/GAS/Attributes/AttibuteSet_Movement.h"

UGA_SkateboardBase::UGA_SkateboardBase()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
}

void UGA_SkateboardBase::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
}

void UGA_SkateboardBase::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

TObjectPtr<class APlayerCharacter> UGA_SkateboardBase::GetSkater(const FGameplayAbilityActorInfo* ActorInfo) const
{
	return ActorInfo ? Cast<APlayerCharacter>(ActorInfo->AvatarActor.Get()) : nullptr;
}

TObjectPtr<class UCharacterMovementComponent> UGA_SkateboardBase::GetMovementComponent(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (const APlayerCharacter* PlayerRef = GetSkater(ActorInfo))
		return PlayerRef->GetCharacterMovement();
	
	return nullptr;
}

TObjectPtr<class UAttibuteSet_Movement> UGA_SkateboardBase::GetMovementSet(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (const APlayerCharacter* PlayerRef = GetSkater(ActorInfo))
		return PlayerRef->GetMoveSet();
	
	return nullptr;
}

bool UGA_SkateboardBase::IsGrounded(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (const UCharacterMovementComponent* CharacterMovementRef = GetMovementComponent(ActorInfo))
		return CharacterMovementRef->IsMovingOnGround();
	
	return false;
}

float UGA_SkateboardBase::GetSpeed2D(const FGameplayAbilityActorInfo* ActorInfo) const
{
	if (const APlayerCharacter* PlayerRef = GetSkater(ActorInfo))
		return PlayerRef->GetVelocity().Size2D();
	
	return 0.f;
}
