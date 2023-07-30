// Fill out your copyright notice in the Description page of Project Settings.


#include "N_BTDecoratorForPathArray.h"

#include "A_WaypointActor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "UObject/UnrealTypePrivate.h"

UN_BTDecoratorForPathArray::UN_BTDecoratorForPathArray()
{
	NodeName = "PathArrayCheck";
}

bool UN_BTDecoratorForPathArray::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		return false;
	}

	UObject* PathObject = Blackboard->GetValueAsObject(GetSelectedBlackboardKey());
	if (!PathObject)
	{
		return false;
	}

	

	// Check if the Path is valid and not empty
	return true;
}
