// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "SkateboardAbilitySystemComponent.generated.h"

UCLASS()
class ANDRESARBONA_TASK_API USkateboardAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
	// Helper to try activate by handle safely
	bool TryActivateAbilityByHandle(const FGameplayAbilitySpecHandle Handle)
	{
		if (!Handle.IsValid()) return false;
		return TryActivateAbility(Handle);
	}

};
