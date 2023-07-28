// Fill out your copyright notice in the Description page of Project Settings.


#include "N_BTTask_PathfinderExperimental.h"

#include "AIController.h"
#include "A_WaypointActor.h" // Include the header for your Waypoint class here
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UN_BTTask_PathfinderExperimental::UN_BTTask_PathfinderExperimental()
{
	NodeName = TEXT("PathFinderExperimental");
}

EBTNodeResult::Type UN_BTTask_PathfinderExperimental::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the AI controller and blackboard component
	AAIController* aiContoller = OwnerComp.GetAIOwner();
	const APawn* AIPawn = aiContoller->GetPawn();
	if (!aiContoller)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		return EBTNodeResult::Failed;
	}

	// Get the StartWaypoint and TargetWaypoint from blackboard
	AA_WaypointActor* startPoint = Cast<AA_WaypointActor>(Blackboard->GetValueAsObject(TEXT("StartWaypoint")));
	AA_WaypointActor* targetPoint = Cast<AA_WaypointActor>(Blackboard->GetValueAsObject(TEXT("TargetWaypoint")));

	if (!startPoint || !targetPoint)
	{
		return EBTNodeResult::Failed;
	}

	// Use A* pathfinding to find the path between StartWaypoint and TargetWaypoint
	TArray<FVector> Path;
	const UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(AIPawn->GetWorld());
	if (navSys)
	{
		//FPathFindingQuery Query(aiContoller, navSys->GetNavDataForProps(aiContoller->GetNavAgentPropertiesRef()), startPoint->GetActorLocation(), targetPoint->GetActorLocation());
		//navSys->FindPathSync(Query, Path);
	}

	// Store the resulting path in the blackboard
	//Blackboard->SetValueAsVector(TEXT("PathToTarget"), Path);
	return EBTNodeResult::Succeeded;
}

FString UN_BTTask_PathfinderExperimental::GetStaticDescription() const
{
	return FString::Printf(TEXT("Static descp"));
}
