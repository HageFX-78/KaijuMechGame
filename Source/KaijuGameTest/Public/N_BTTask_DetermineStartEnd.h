// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "A_PathfindingManager.h"
#include "N_BTTask_DetermineStartEnd.generated.h"

/**
 * 
 */
UCLASS()
class KAIJUGAMETEST_API UN_BTTask_DetermineStartEnd : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UN_BTTask_DetermineStartEnd();

	UPROPERTY(BlueprintReadWrite, Category = "Pathfinding")
	AA_PathfindingManager* PFMan;
	
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	
};
