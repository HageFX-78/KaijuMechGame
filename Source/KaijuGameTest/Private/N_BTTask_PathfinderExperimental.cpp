// Fill out your copyright notice in the Description page of Project Settings.


#include "N_BTTask_PathfinderExperimental.h"

#include "AIController.h"
#include "A_PathfindingManager.h"
#include "A_WaypointActor.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

UN_BTTask_PathfinderExperimental::UN_BTTask_PathfinderExperimental()
{
	NodeName = TEXT("Roam Node Supposedly");
}

EBTNodeResult::Type UN_BTTask_PathfinderExperimental::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		return EBTNodeResult::Failed;
	}
	//Reference pathfinder manager singleton
	PFMan = Cast<AA_PathfindingManager>(Blackboard->GetValueAsObject(TEXT("PFManager")));
	if (!PFMan)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PFM not found, maybe not in scene"));
		return EBTNodeResult::Failed;
	}
	
	
	/*// Get the AI controller and blackboard component
	AAIController* aiContoller = OwnerComp.GetAIOwner();
	const APawn* AIPawn = aiContoller->GetPawn();
	if (!aiContoller)
	{
		return EBTNodeResult::Failed;
	}*/

	//Black board component
	

	// Get the StartWaypoint and TargetWaypoint from blackboard
	AA_WaypointActor* StartPoint = Cast<AA_WaypointActor>(Blackboard->GetValueAsObject(TEXT("StartWaypoint")));
	AA_WaypointActor* TargetPoint = Cast<AA_WaypointActor>(Blackboard->GetValueAsObject(TEXT("TargetWaypoint")));

	if (!StartPoint || !TargetPoint)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Start or target point not found"));
		return EBTNodeResult::Failed;
	}

	// Uses built in Nav system and Navmesh, the reason i avoided blueprints in the firstplace
	// TArray<FVector> Path;
	// const UNavigationSystemV1* navSys = UNavigationSystemV1::GetCurrent(AIPawn->GetWorld());
	/*if (navSys)
	{
		
	}*/

	TArray<AA_WaypointActor*> Path = PFMan->FindPath(StartPoint, TargetPoint);

	FString ConcatenatedNames;
	for (AA_WaypointActor* wp : Path)
	{
		ConcatenatedNames += wp->pointName + TEXT("->"); // Add the waypoint name and a comma-space separator
	}

	// Print the concatenated names to the log using AddOnScreenDebugMessage
	GEngine->AddOnScreenDebugMessage(5, 10.f, FColor::Green, FString::Printf(TEXT("Path: %s"), *ConcatenatedNames));
	
	// Store the resulting path in the blackboard
	//Blackboard->SetValueAsVector(TEXT("PathToTarget"), Path);
	return EBTNodeResult::Succeeded;
}

FString UN_BTTask_PathfinderExperimental::GetStaticDescription() const
{
	return FString::Printf(TEXT("Roam behaviour, or maybe it's not..."));
}
