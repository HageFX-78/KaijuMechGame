// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "N_BTDecoratorForPathArray.generated.h"

/**
 * 
 */
UCLASS()
class KAIJUGAMETEST_API UN_BTDecoratorForPathArray : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()

public:
	UN_BTDecoratorForPathArray();
protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
