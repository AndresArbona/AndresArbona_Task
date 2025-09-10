#include "AndresArbona_Task/Obstacle/Obstacle.h"

#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AndresArbona_Task/GAS/SkateboardGameplayTagsList.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = false;

	GateIn = CreateDefaultSubobject<UBoxComponent>(TEXT("GateIn"));  
	GateOut = CreateDefaultSubobject<UBoxComponent>(TEXT("GateOut"));

	GateIn->SetCollisionProfileName(TEXT("OverlapAll"));
	RootComponent = GateIn;
	
	GateOut->SetupAttachment(RootComponent); 
	GateOut->SetCollisionProfileName(TEXT("OverlapAll")); 
	GateOut->SetRelativeLocation(FVector(200.f, 0.f, 0.f));
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	GateIn->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnGateInOverlap);
	GateOut->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnGateOutOverlap);
}

void AObstacle::OnGateInOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) 
	{ 
		ActiveRunners.Add(OtherActor); 
	}
}

void AObstacle::OnGateOutOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor || !ActiveRunners.Contains(OtherActor)) return;
	ActiveRunners.Remove(OtherActor);

	if (const ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		if (const UCharacterMovementComponent* CharacterMovementComp = Character->GetCharacterMovement())
		{
			const bool bAir = !CharacterMovementComp->IsMovingOnGround();
			if (bAir)
			{
				FGameplayEventData EventData; 
				EventData.EventMagnitude = (float)Points; 
				EventData.Instigator = this; 
				EventData.Target = OtherActor;

				UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(OtherActor, SkateTags::Event_ObstacleCleared(), EventData);
			}
		}
	}
}


