// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SkateMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ANDRESARBONA_TASK_API USkateMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	USkateMovementComponent();
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	virtual void BeginPlay() override;

private:
	TObjectPtr<class UAbilitySystemComponent> ASC = nullptr;
	const class UAttibuteSet_Movement* MovementSet{};
	TObjectPtr<class UCharacterMovementComponent> MovementComponent = nullptr;

	float GetSpeed2D() const;
		
};
