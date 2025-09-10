// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class ANDRESARBONA_TASK_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	AObstacle();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* GateIn;
	UPROPERTY(VisibleAnywhere)
	class UBoxComponent* GateOut;
	UPROPERTY(EditAnywhere, Category = "Skate|Score")
	int32 Points = 100;

	UFUNCTION() void OnGateInOverlap(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);
	
	UFUNCTION() void OnGateOutOverlap(UPrimitiveComponent* OverlappedComp, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		int32 OtherBodyIndex, 
		bool bFromSweep, 
		const FHitResult& SweepResult);

	TSet<TWeakObjectPtr<AActor>> ActiveRunners;
};
