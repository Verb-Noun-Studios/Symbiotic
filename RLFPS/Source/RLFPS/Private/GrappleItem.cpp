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

void UGrappleItem::OnActiveAbility_Implementation(AActor* gun)
{ 

	UWorld* World = GetWorld();
	FHitResult result;
	FVector start = gun->GetActorLocation() + gun->GetActorForwardVector() * minGrappleDistance;
	FCollisionQueryParams CollisionParameters;
	FVector end = gun->GetActorLocation() + gun->GetActorForwardVector() * maxGrappleDistance;

	World->LineTraceSingleByChannel(result, start, end, ECollisionChannel::ECC_Visibility);
	DrawDebugLine(GetWorld(), start, end, FColor::Green, true, 5, 0, 3);
	//GEngine->AddOnScreenDebugMessage(-1, 0.10f, FColor::Yellow, TEXT("ActiveItem"));
	//UE_LOG(LogTemp, Warning, TEXT("Calling On Active"));

	if (result.IsValidBlockingHit())
	{
		AActor* newActor = SpawnActorOfClass_Internal(gun, classToSpawn, gun->GetActorLocation(), gun->GetActorRotation());

		AGrapple* grapple = Cast<AGrapple>(newActor);
		grapple->startLoc = start;
		grapple->endLoc = result.ImpactPoint;
		grapple->OnStart(gun, result.Actor.Get(), grapple->endLoc - result.Actor.Get()->GetActorLocation() );
	

	}

	


}

