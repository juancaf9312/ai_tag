// Fill out your copyright notice in the Description page of Project Settings.

#include "TagController.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void ATagController::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::GetAllActorsOfClass(this, ATargetPoint::StaticClass(), Waypoints);

	GoToRandomWaypoint();
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
