// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/PlayerCharacter/PlayerCharacter.h"

#include "AndresArbona_Task/GAS/SkateboardAbilitySystemComponent.h"
#include "AndresArbona_Task/GAS/Attributes/AttibuteSet_Movement.h"
#include "AndresArbona_Task/GAS/Attributes/AttributeSet_Score.h"
#include "AndresArbona_Task/Components/SkateMovementComponent.h"
#include "GameplayEffect.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "AndresArbona_Task/GAS/Enum/ESkateboardInputs.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	ASC = CreateDefaultSubobject<USkateboardAbilitySystemComponent>(TEXT("ASC"));
	MovementSet = CreateDefaultSubobject<UAttibuteSet_Movement>(TEXT("MovementSet"));
	ScoreSet = CreateDefaultSubobject<UAttributeSet_Score>(TEXT("ScoreSet"));

	SkateMovementComponent = CreateDefaultSubobject<USkateMovementComponent>(TEXT("SkateMovementComponent"));

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 350.f; 
	SpringArm->bUsePawnControlRotation = true; 
	SpringArm->bEnableCameraLag = true; 
	SpringArm->CameraLagSpeed = 10.f;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	SkateStaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SkateMesh"));
	SkateStaticMesh->SetupAttachment(GetMesh());

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

UAbilitySystemComponent* APlayerCharacter::GetAbilitySystemComponent() const { return ASC; }


void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeAttributes();
	GiveDefaultAbilities();
}

void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool APlayerCharacter::IsGrounded() const
{
	return GetCharacterMovement() && GetCharacterMovement()->IsMovingOnGround();
}

float APlayerCharacter::GetSpeed2D() const
{
	return GetVelocity().Size2D();
}

void APlayerCharacter::InitializeAttributes()
{
	if (ASC && GE_StartupAttributes)
	{
		FGameplayEffectContextHandle Ctx = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle Spec = ASC->MakeOutgoingSpec(GE_StartupAttributes, 1.f, Ctx);
		if (Spec.IsValid()) { ASC->ApplyGameplayEffectSpecToSelf(*Spec.Data.Get()); }
	}
}

void APlayerCharacter::GiveDefaultAbilities()
{
	if (!ASC || !HasAuthority()) return;
	
	if (GA_PushClass)
	{
		PushHandle = ASC->GiveAbility(
			FGameplayAbilitySpec(GA_PushClass, 1,
				static_cast<int32>(ESkateboardInputs::Push), this));
	}
	if (GA_BrakeClass)
	{
		BrakeHandle = ASC->GiveAbility(
			FGameplayAbilitySpec(GA_BrakeClass, 1,
				static_cast<int32>(ESkateboardInputs::Brake), this));
	}
	if (GA_JumpClass)
	{
		JumpHandle = ASC->GiveAbility(
			FGameplayAbilitySpec(GA_JumpClass, 1,
				static_cast<int32>(ESkateboardInputs::Jump), this));
	}
}