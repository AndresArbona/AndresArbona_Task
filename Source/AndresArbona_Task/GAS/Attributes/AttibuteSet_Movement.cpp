// Fill out your copyright notice in the Description page of Project Settings.


#include "AndresArbona_Task/GAS/Attributes/AttibuteSet_Movement.h"

UAttibuteSet_Movement::UAttibuteSet_Movement()
{
	InitMaxSpeed(1200.f);
	InitAcceleration(2048.f);
	InitGroundFriction(3.5f);
	InitBrakingDeceleration(1400.f);
	InitAirControl(0.2f);
	InitTurnRateLow(90.f);
	InitTurnRateHigh(45.f);
	InitSpeedHighAt(1200.f);
	InitJumpImpulse(480.f);
	InitMinJumpSpeed(300.f);
}
