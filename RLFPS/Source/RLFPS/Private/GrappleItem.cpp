// Fill out your copyright notice in the Description page of Project Settings.


#include "GrappleItem.h"
#include "Grapple.h"


UGrappleItem::UGrappleItem()
{

}

UGrappleItem::~UGrappleItem()
{

}

void UGrappleItem::OnActiveItem_Implementation(AActor* actor)
{ 
	AActor* newActor = SpawnActorOfClass_Internal(actor, classToSpawn, actor->GetActorLocation(), actor->GetActorRotation());

	AGrapple* grapple = Cast<AGrapple>(newActor);



	grapple->startLoc = actor->GetActorLocation();


}