// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"

#include "AttibuteSet_Movement.generated.h"

#define SKATE_ATTR_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class ANDRESARBONA_TASK_API UAttibuteSet_Movement : public UAttributeSet
{
	GENERATED_BODY()
	
public: 
	UAttibuteSet_Movement();

	//Speed
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Skateboard | Move")
	FGameplayAttributeData MaxSpeed; SKATE_ATTR_ACCESSORS(UAttibuteSet_Movement, MaxSpeed);
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skateboard | Move")
	FGameplayAttributeData Acceleration; SKATE_ATTR_ACCESSORS(UAttibuteSet_Movement, Acceleration)

	//Physics
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skateboard | Move")
	FGameplayAttributeData GroundFriction; SKATE_ATTR_ACCESSORS(UAttibuteSet_Movement, GroundFriction)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skateboard | Move")
	FGameplayAttributeData BrakingDeceleration; SKATE_ATTR_ACCESSORS(UAttibuteSet_Movement, BrakingDeceleration)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skateboard | Move")
	FGameplayAttributeData AirControl; SKATE_ATTR_ACCESSORS(UAttibuteSet_Movement, AirControl)

	//Turning
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skateboard | Move")
	FGameplayAttributeData TurnRateLow; SKATE_ATTR_ACCESSORS(UAttibuteSet_Movement, TurnRateLow)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skateboard | Move")
	FGameplayAttributeData TurnRateHigh; SKATE_ATTR_ACCESSORS(UAttibuteSet_Movement, TurnRateHigh)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skateboard | Move")
	FGameplayAttributeData SpeedHighAt; SKATE_ATTR_ACCESSORS(UAttibuteSet_Movement, SpeedHighAt)

	//Jump
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skateboard | Move")
	FGameplayAttributeData JumpImpulse; SKATE_ATTR_ACCESSORS(UAttibuteSet_Movement, JumpImpulse)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Skateboard | Move")
	FGameplayAttributeData MinJumpSpeed; SKATE_ATTR_ACCESSORS(UAttibuteSet_Movement, MinJumpSpeed)

};
