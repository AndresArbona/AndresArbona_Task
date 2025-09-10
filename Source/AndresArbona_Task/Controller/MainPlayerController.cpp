// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/Controller/MainPlayerController.h"

#include "InputAction.h"
#include "InputModifiers.h"
#include "InputMappingContext.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "AndresArbona_Task/GAS/SkateboardAbilitySystemComponent.h"

AMainPlayerController::AMainPlayerController() 
{
	
}

void AMainPlayerController::SetupInputComponent()
{

	Super::SetupInputComponent();

	if (MoveAction = NewObject<UInputAction>(); MoveAction)
	MoveAction->ValueType = EInputActionValueType::Axis2D;

	if (LookAction = NewObject<UInputAction>(); LookAction)
	LookAction->ValueType = EInputActionValueType::Axis2D;

	if (PushAction = NewObject<UInputAction>(); PushAction)
	PushAction->ValueType = EInputActionValueType::Boolean;

	if (BrakeAction = NewObject<UInputAction>(); BrakeAction)
	BrakeAction->ValueType = EInputActionValueType::Boolean;

	if (JumpAction = NewObject<UInputAction>(); JumpAction)
	JumpAction->ValueType = EInputActionValueType::Boolean;

	if (MappingContext = NewObject<UInputMappingContext>(); MappingContext)
	{
		auto& Move_Foward = MappingContext->MapKey(MoveAction, EKeys::W);
		UInputModifierSwizzleAxis* Swizzle_Modifier_Front = NewObject<UInputModifierSwizzleAxis>(); Swizzle_Modifier_Front->Order = EInputAxisSwizzle::YXZ; Move_Foward.Modifiers.Add(Swizzle_Modifier_Front);

		auto& Move_Right = MappingContext->MapKey(MoveAction, EKeys::D);
		UInputModifierSwizzleAxis* Swizzle_Modifier_Right = NewObject<UInputModifierSwizzleAxis>(); Swizzle_Modifier_Right->Order = EInputAxisSwizzle::XZY; Move_Right.Modifiers.Add(Swizzle_Modifier_Right);

		auto& Move_Left = MappingContext->MapKey(MoveAction, EKeys::A);
		UInputModifierSwizzleAxis* Swizzle_Modifier_Left = NewObject<UInputModifierSwizzleAxis>(); Swizzle_Modifier_Left->Order = EInputAxisSwizzle::XZY; Move_Left.Modifiers.Add(Swizzle_Modifier_Left);
		UInputModifierNegate* Negate_Modifier = NewObject<UInputModifierNegate>(); Negate_Modifier->bX = true; Move_Left.Modifiers.Add(Negate_Modifier);

		MappingContext->MapKey(LookAction, EKeys::Mouse2D);

		MappingContext->MapKey(PushAction, EKeys::LeftShift);

		MappingContext->MapKey(BrakeAction, EKeys::LeftControl);

		MappingContext->MapKey(JumpAction, EKeys::SpaceBar);

		if (auto* const Enhanced_Input_Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
		{
			Enhanced_Input_Subsystem->ClearAllMappings();
			Enhanced_Input_Subsystem->AddMappingContext(MappingContext, 0);
		}
	}

	if (auto* const Enhanced_Input_Component = Cast<UEnhancedInputComponent>(InputComponent))
	{
		Enhanced_Input_Component->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMainPlayerController::OnMove);
		Enhanced_Input_Component->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMainPlayerController::OnLook);

		Enhanced_Input_Component->BindAction(JumpAction, ETriggerEvent::Started, this, &AMainPlayerController::OnJumpStarted);
		Enhanced_Input_Component->BindAction(BrakeAction, ETriggerEvent::Started, this, &AMainPlayerController::OnBrakeStarted);
		Enhanced_Input_Component->BindAction(BrakeAction, ETriggerEvent::Completed, this, &AMainPlayerController::OnBrakeCompleted);
		Enhanced_Input_Component->BindAction(PushAction, ETriggerEvent::Started, this, &AMainPlayerController::OnPushStarted);
		Enhanced_Input_Component->BindAction(PushAction, ETriggerEvent::Completed, this, &AMainPlayerController::OnPushCompleted);
	}
}

APlayerCharacter* AMainPlayerController::GetSkatePawn()
{
	return Cast<APlayerCharacter>(GetPawn());
}


void AMainPlayerController::OnMove(const FInputActionValue& Value) 
{
	
	if (APlayerCharacter* PlayerRef = GetSkatePawn())
	{
		const FVector2D InputAxis2D = Value.Get<FVector2D>();

		PlayerRef->SetThrottle(FMath::Clamp(InputAxis2D.Y, 0.f, 1.f));   // W solo acelera (sin reversa)
		PlayerRef->SetSteer(FMath::Clamp(InputAxis2D.X, -1.f, 1.f));     // A/D = timón

	}
}
void AMainPlayerController::OnLook(const FInputActionValue& Value)
{
	const FVector2D InputAxis2D = Value.Get<FVector2D>();
	AddYawInput(InputAxis2D.X);
	AddPitchInput(InputAxis2D.Y);
}

void AMainPlayerController::OnPushStarted(const FInputActionValue& Value)
{
	if (APlayerCharacter* PlayerRef = GetSkatePawn())
	{
		if (USkateboardAbilitySystemComponent* ASC = PlayerRef->GetSkateASC())
		{
			ASC->TryActivateAbilityByHandle(PlayerRef->PushHandle);
		}
	}
}
void AMainPlayerController::OnPushCompleted(const FInputActionValue& Value)
{

}
void AMainPlayerController::OnBrakeStarted(const FInputActionValue& Value)
{
	if (APlayerCharacter* PlayerRef = GetSkatePawn())
	{
		if (USkateboardAbilitySystemComponent* ASC = PlayerRef->GetSkateASC())
		{
			ASC->TryActivateAbilityByHandle(PlayerRef->BrakeHandle);
		}
	}
}
void AMainPlayerController::OnBrakeCompleted(const FInputActionValue& Value)
{

}
void AMainPlayerController::OnJumpStarted(const FInputActionValue& Value)
{
	if (APlayerCharacter* PlayerRef = GetSkatePawn())
	{
		if (USkateboardAbilitySystemComponent* ASC = PlayerRef->GetSkateASC())
		{
			ASC->TryActivateAbilityByHandle(PlayerRef->JumpHandle);
		}
	}
}