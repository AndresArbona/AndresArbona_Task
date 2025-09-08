// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameplayTagContainer.h"

namespace SkateTags
{
	inline FGameplayTag State_Grounded() { return FGameplayTag::RequestGameplayTag(FName("State.Movement.Grounded")); }
	inline FGameplayTag State_Grounded() { return FGameplayTag::RequestGameplayTag(FName("State.Movement.Airbone")); }
	inline FGameplayTag State_Grounded() { return FGameplayTag::RequestGameplayTag(FName("State.Movement.Pushing")); }
	inline FGameplayTag State_Grounded() { return FGameplayTag::RequestGameplayTag(FName("State.Movement.Braking")); }

	inline FGameplayTag Cooldown_Push() { return FGameplayTag::RequestGameplayTag(FName("Cooldown.Push")); }

	inline FGameplayTag Event_ObstableCleared() { return FGameplayTag::RequestGameplayTag(FName("Event.ObstacleCleared")); }
	inline FGameplayTag Even_JumpCommited() { return FGameplayTag::RequestGameplayTag(FName("Cooldown.JumpCommited")); }
	inline FGameplayTag Event_Landed() { return FGameplayTag::RequestGameplayTag(FName("Cooldown.Landed")); }

	inline FGameplayTag Cue_Push() { return FGameplayTag::RequestGameplayTag(FName("GameplayCue.Push")); }
	inline FGameplayTag Cue_Brake() { return FGameplayTag::RequestGameplayTag(FName("GameplayCue.Brake")); }
	inline FGameplayTag Cue_Jump() { return FGameplayTag::RequestGameplayTag(FName("GameplayCue.Jump")); }
	inline FGameplayTag Cue_Land() { return FGameplayTag::RequestGameplayTag(FName("GameplayCue.Land")); }
	inline FGameplayTag Cue_Score() { return FGameplayTag::RequestGameplayTag(FName("GameplayCue.Score")); }
};
