#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include <AndresArbona_Task/PlayerCharacter/PlayerCharacter.h>

#include "MainPlayerController.generated.h"
/**
 * 
 */
UCLASS()
class ANDRESARBONA_TASK_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMainPlayerController();

private:
	void SetupInputComponent() override;

	UPROPERTY() 
	TObjectPtr<class UInputMappingContext> MappingContext{};
	UPROPERTY() 
	TObjectPtr<class UInputAction> MoveAction;
	UPROPERTY() 
	TObjectPtr<class UInputAction> LookAction;
	UPROPERTY()
	TObjectPtr<class UInputAction> PushAction;
	UPROPERTY()
	TObjectPtr<class UInputAction> BrakeAction;
	UPROPERTY() 
	TObjectPtr<class UInputAction> JumpAction;

	// Handlers
	void OnMove(const struct FInputActionValue& Value);
	void OnLook(const struct FInputActionValue& Value);
	void OnPushStarted(const struct FInputActionValue& Value);
	void OnPushCompleted(const struct FInputActionValue& Value);
	void OnBrakeStarted(const struct FInputActionValue& Value);
	void OnBrakeCompleted(const struct FInputActionValue& Value);
	void OnJumpStarted(const struct FInputActionValue& Value);

	APlayerCharacter* GetSkatePawn() const;
};
