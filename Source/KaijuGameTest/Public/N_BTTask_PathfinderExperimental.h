// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "N_BTTask_PathfinderExperimental.generated.h"

/**
 * 
 */
UCLASS()
class KAIJUGAMETEST_API UN_BTTask_PathfinderExperimental : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UN_BTTask_PathfinderExperimental();
private:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
	
};
