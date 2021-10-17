// Fill out your copyright notice in the Description page of Project Settings.


#include "HomingMod.h"
#include "Bullet.h"


UHomingMod::UHomingMod()
{

}


UHomingMod::~UHomingMod()
{

}


void UHomingMod::OnSpawn(ABullet* bullet)
{

	
	bullet->ProjectileMovementComponent->bIsHomingProjectile = true;
	bullet->HomingStrength = bullet->initialHomingStrength + (bullet->HomingStackingStrength * stacks);
	bullet->ProjectileMovementComponent->HomingAccelerationMagnitude = bullet->HomingStrength;
	float range = bullet->initialHomingRange + (bullet->HomingRangeStackingStrength * stacks);
	UE_LOG(LogTemp, Warning, TEXT("Setting Homing Range: %f "), range);
	bullet->homingRange = range;
}