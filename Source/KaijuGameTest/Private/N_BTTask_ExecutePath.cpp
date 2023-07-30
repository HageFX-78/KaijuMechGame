// Fill out your copyright notice in the Description page of Project Settings.


#include "N_BTTask_ExecutePath.h"

UN_BTTask_ExecutePath::UN_BTTask_ExecutePath()
{
	NodeName = TEXT("Move Along Path");
}

EBTNodeResult::Type UN_BTTask_ExecutePath::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		return EBTNodeResult::Failed;
	}
	
	Blackboard->SetValueAsBool(TEXT("pathfindingReady"), false);
	return EBTNodeResult::Succeeded;
}

FString UN_BTTask_ExecutePath::GetStaticDescription() const
{
	return FString::Printf(TEXT("Execute movement."));
}
