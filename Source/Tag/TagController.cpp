// Fill out your copyright notice in the Description page of Project Settings.

#include "TagController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/GameFramework/Character.h"
#include "Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

void ATagController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), Waypoints);

	GoToRandomWaypoint();

	auto Character = GetCharacter();

	if (Character)
	{
		Character->LandedDelegate.AddUniqueDynamic(this, &ATagController::OnLanded);
		Character->MovementModeChangedDelegate.AddUniqueDynamic(this, &ATagController::OnMovementModeChanged);
	}
}

void ATagController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult & Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	GetWorldTimerManager().SetTimer(TimerHandle, this, &ATagController::GoToRandomWaypoint, 1.0f, false);
}

ATargetPoint* ATagController::GetRandomWaypoint()
{
	auto index = FMath::RandRange(0, Waypoints.Num() - 1);
	return Cast<ATargetPoint>(Waypoints[index]);
}

void ATagController::GoToRandomWaypoint()
{
	MoveToActor(GetRandomWaypoint());
}

void ATagController::OnMovementModeChanged(ACharacter* MovedCharacter, EMovementMode PrevMovementMode, uint8 PreviousCustomMode /*= 0*/)
{
	// If the new movement mode is Falling
	if (MovedCharacter->GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Falling)
	{
		GetPathFollowingComponent()->Deactivate();
	}
}

void ATagController::OnLanded(const FHitResult & Hit)
{
	GetPathFollowingComponent()->Activate();
}
