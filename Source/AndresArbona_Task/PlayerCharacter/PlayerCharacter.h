// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include <GameplayAbilitySpecHandle.h>

#include "PlayerCharacter.generated.h"

class UGameplayAbility; class UGameplayEffect;

UCLASS()
class ANDRESARBONA_TASK_API APlayerCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;


	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	void InitializeAttributes();
	void GiveDefaultAbilities();

	TObjectPtr<class USkateboardAbilitySystemComponent> GetSkateASC() const { return ASC; }
	TObjectPtr<class UAttibuteSet_Movement> GetMoveSet() const { return MovementSet; }
	TObjectPtr<class UAttributeSet_Score> GetScoreSet() const { return ScoreSet; }

	// Ability handles (for direct activation/cancel from Controller)
	FGameplayAbilitySpecHandle PushHandle;
	FGameplayAbilitySpecHandle BrakeHandle;
	FGameplayAbilitySpecHandle JumpHandle;

	UPROPERTY(EditDefaultsOnly, Category = "Skate|GAS") TSubclassOf<UGameplayEffect> GE_StartupAttributes;
	UPROPERTY(EditDefaultsOnly, Category = "Skate|GAS") TSubclassOf<UGameplayAbility> GA_PushClass;
	UPROPERTY(EditDefaultsOnly, Category = "Skate|GAS") TSubclassOf<UGameplayAbility> GA_BrakeClass;
	UPROPERTY(EditDefaultsOnly, Category = "Skate|GAS") TSubclassOf<UGameplayAbility> GA_JumpClass;

	bool IsGrounded() const;
	float GetSpeed2D() const;

private:
	UPROPERTY(EditAnywhere, Category = "Config|Components")
	TObjectPtr<class USpringArmComponent> SpringArm{};
	UPROPERTY(EditAnywhere, Category = "Config|Components")
	TObjectPtr<class UCameraComponent> Camera{};
	UPROPERTY(EditAnywhere, Category = "Config|Components")
	TObjectPtr<class UStaticMeshComponent> SkateStaticMesh{};
	UPROPERTY(EditAnywhere, Category = "Config|Components")
	TObjectPtr<class USkateMovementComponent> SkateMovementComponent{};

	UPROPERTY() 
	TObjectPtr <class USkateboardAbilitySystemComponent> ASC;
	UPROPERTY() 
	TObjectPtr <class UAttibuteSet_Movement> MovementSet;
	UPROPERTY() 
	TObjectPtr <class UAttributeSet_Score> ScoreSet;
};
