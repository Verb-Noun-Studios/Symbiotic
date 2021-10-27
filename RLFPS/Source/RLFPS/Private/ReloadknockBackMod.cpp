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

void UReloadKnockBackMod::OnReload(AActor* actor)
{
	TArray<AActor*> enemies;

	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, enemies);

	for (AActor* enemy : enemies)
	{
		FVector dir =  enemy->GetActorLocation() - actor->GetActorLocation();
		float distance = dir.Size();
		dir.Normalize();
		UE_LOG(LogTemp, Warning, TEXT("Reload knockback: TestingDistance to Enemy, Distance: %f"), distance);

		if (distance < range + additionalRangePerStack * stacks)
		{
			AGruntCharacter* character = Cast<AGruntCharacter>(enemy);

			character->GetMovementComponent()->Velocity += dir * (strength + additionalStrengthPerStack * stacks);
			//character->GetMesh()->AddForce(dir * (strength + additionalStrengthPerStack * stacks) * character->GetMesh()->GetMass());
			//UE_LOG(LogTemp, Warning, TEXT("Reload knockback: adding Force to enemy, Distance: %f"), strength + additionalStrengthPerStack * stacks);

			
		}


	}
}