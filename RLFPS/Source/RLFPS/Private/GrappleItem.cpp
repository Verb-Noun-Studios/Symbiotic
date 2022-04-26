// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleItem.h"
#include "Grapple.h"
#include "DrawDebugHelpers.h"


UGrappleItem::UGrappleItem()
{

}

UGrappleItem::~UGrappleItem()
{

}

void UGrappleItem::LaunchGrapple(AActor* gun)
{ 

	UWorld* World = GetWorld();
	FHitResult result;
	FVector start = gun->GetActorLocation() + gun->GetActorForwardVector() * minGrappleDistance;
	FCollisionQueryParams CollisionParameters;
	FCollisionShape shape;
	shape.SetSphere(50);
	FVector end = gun->GetActorLocation() + gun->GetActorForwardVector() * maxGrappleDistance;
	
	World->LineTraceSingleByChannel(result, gun->GetActorLocation(), start, ECollisionChannel::ECC_Visibility);
	

	if (result.IsValidBlockingHit() && result.Actor != gun)
	{
		
		return;
	}

	World->LineTraceSingleByChannel(result, start, end, ECollisionChannel::ECC_Visibility);

	World->SweepSingleByChannel(result, start, end, FQuat(0, 0, 0, 0), ECollisionChannel::ECC_WorldStatic, shape, CollisionParameters, FCollisionResponseParams::DefaultResponseParam);

	if (result.IsValidBlockingHit())
	{
		AActor* newActor = SpawnActorOfClass_Internal(gun, classToSpawn, gun->GetActorLocation(), gun->GetActorRotation());

		AGrapple* grapple = Cast<AGrapple>(newActor);
		grapple->startLoc = start;
		grapple->endLoc = result.ImpactPoint;
		grapple->OnStart(gun);
		
		currentKillCount = 0;

	}

}

