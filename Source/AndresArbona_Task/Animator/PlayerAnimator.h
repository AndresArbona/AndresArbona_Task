// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AndresArbona_Task/GAS/SkateboardGameplayTagsList.h"

#include "PlayerAnimator.generated.h"

class UAbilitySystemComponent; class UAnimSequence; class UAnimMontage; class ACharacter;

UCLASS()
class ANDRESARBONA_TASK_API UPlayerAnimator : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Anim") 
	float SpeedForRoll = 200.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Anim") 
	FName SlotName = FName("DefaultSlot");
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Anim") 
	float BaseBlendIn = 0.08f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Anim") 
	float BaseBlendOut = 0.12f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Anim") 
	float OneShotBlendIn = 0.06f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Anim") 
	float OneShotBlendOut = 0.12f;

	// Assets
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Anim") 
	UAnimSequence* IdleLoop = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Anim") 
	UAnimSequence* RollLoop = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Anim") 
	UAnimSequence* PushAnim = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Anim") 
	UAnimSequence* JumpAnim = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Skate|Anim") 
	UAnimSequence* LandAnim = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skate|State") 
	float Speed = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skate|State") 
	bool bGrounded = true;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skate|State") 
	bool bPushing = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Skate|State") 
	bool bBraking = false;

private:
	TWeakObjectPtr<ACharacter> OwnerChararacter;
	TWeakObjectPtr<UAbilitySystemComponent> ASC;

	// cache de transiciones
	bool bPrevGrounded = true;
	bool bPrevPushing = false;

	// para saber cuál base está activa
	UAnimSequence* CurrentBaseSequence = nullptr;

	void EnsureBaseLoop();
	void PlayOneShot(UAnimSequence* Sequence);
};
