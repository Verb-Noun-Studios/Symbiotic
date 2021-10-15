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

	bullet->ProjectileMovementComponent->HomingAccelerationMagnitude = bullet->initialHomingStrength + (bullet->HomingStackingStrength);
	bullet->homingRange = bullet->initialHomingRange + (bullet->HomingRangeStackingStrength);
}