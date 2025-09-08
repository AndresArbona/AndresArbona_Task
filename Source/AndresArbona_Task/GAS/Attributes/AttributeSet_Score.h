// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet_Score.generated.h"

/**
 * 
 */
UCLASS()
class ANDRESARBONA_TASK_API UAttributeSet_Score : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAttributeSet_Score() {}


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Score") FGameplayAttributeData Score;
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(UAttributeSet_Score, Score)
		GAMEPLAYATTRIBUTE_VALUE_GETTER(Score)
		GAMEPLAYATTRIBUTE_VALUE_SETTER(Score)
		GAMEPLAYATTRIBUTE_VALUE_INITTER(Score)
};
