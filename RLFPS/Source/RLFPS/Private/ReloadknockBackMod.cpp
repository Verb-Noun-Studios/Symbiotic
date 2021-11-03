// Fill out your copyright notice in the Description page of Project Settings.


#include "ReloadknockBackMod.h"
#include "GruntCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PawnMovementComponent.h"

UReloadKnockBackMod::UReloadKnockBackMod()
{

}


UReloadKnockBackMod::~UReloadKnockBackMod()
{

}

void UReloadKnockBackMod::OnReload_Implementation(AActor* player)
{
	TArray<AActor*> enemies;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, enemies);

	for (AActor* enemy : enemies)
	{
		FVector dir =  enemy->GetActorLocation() - player->GetActorLocation();
		float distance = dir.Size();
		dir.Normalize();
		UE_LOG(LogTemp, Warning, TEXT("Reload knockback: TestingDistance to Enemy, Distance: %f"), distance);

		if (distance < range + additionalRangePerStack * stacks)
		{
			AGruntCharacter* character = Cast<AGruntCharacter>(enemy);
			character->LaunchCharacter(dir * (strength + additionalStrengthPerStack * stacks), true, true);
		}


	}
}