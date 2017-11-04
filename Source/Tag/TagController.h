// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Runtime/Engine/Classes/Engine/TargetPoint.h"
#include "TagController.generated.h"

/**
 *
 */
UCLASS()
class TAG_API ATagController : public AAIController
{
	GENERATED_BODY()

public:
	void BeginPlay() override;

	void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

private:
	FTimerHandle TimerHandle;

	UPROPERTY()
		TArray<AActor*> Waypoints;

	UFUNCTION(BlueprintPure)
		ATargetPoint* GetRandomWaypoint();

	UFUNCTION(BlueprintCallable)
		void GoToRandomWaypoint();

	UFUNCTION()
		void OnMovementModeChanged(ACharacter* MovedCharacter, EMovementMode PrevMovementMode, uint8 PreviousCustomMode = 0);

	UFUNCTION()
		void OnLanded(const FHitResult& Hit);
};
