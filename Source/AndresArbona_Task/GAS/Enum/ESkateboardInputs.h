// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"

UENUM(blueprintType)
enum class EStakeboardInputID : uint8
{
	None UMETA(DisplayName = "None"),
	Push UMETA(DisplayName = "Push"),
	Brake UMETA(DisplayName = "Brake"),
	Jump UMETA(DisplayName = "Jump")
};

