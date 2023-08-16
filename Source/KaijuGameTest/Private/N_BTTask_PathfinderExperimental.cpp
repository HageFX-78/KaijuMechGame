// Fill out your copyright notice in the Description page of Project Settings.


#include "N_BTTask_PathfinderExperimental.h"

#include "AIController.h"
#include "A_PathfindingManager.h"
#include "A_WaypointActor.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NewCustomPathArray.h"
#include "Navigation/PathFollowingComponent.h"

UN_BTTask_PathfinderExperimental::UN_BTTask_PathfinderExperimental()
{
	NodeName = TEXT("Roam Node Supposedly");
}

EBTNodeResult::Type UN_BTTask_PathfinderExperimental::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get blackboard
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Blackboard)
	{
		return EBTNodeResult::Failed;
	}

	
	//Reference pathfinder manager
	PFMan = Cast<AA_PathfindingManager>(Blackboard->GetValueAsObject(TEXT("PFManager")));
	if (!PFMan)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("PFM not found, maybe not in scene"));
		return EBTNodeResult::Failed;
	}
	

	// Get the StartWaypoint and TargetWaypoint from blackboard
	AA_WaypointActor* StartPoint = Cast<AA_WaypointActor>(Blackboard->GetValueAsObject(TEXT("StartWaypoint")));
	AA_WaypointActor* TargetPoint = Cast<AA_WaypointActor>(Blackboard->GetValueAsObject(TEXT("TargetWaypoint")));

	if (!StartPoint || !TargetPoint)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Red, TEXT("Start or target point not found"));
		return EBTNodeResult::Failed;
	}


	
	//Use findpath function from pathfindingmanager
	TArray<AA_WaypointActor*> Path = PFMan->FindPath(StartPoint, TargetPoint);

	if(Path.IsEmpty())
	{
		GEngine->AddOnScreenDebugMessage(-1, 4.f, FColor::Red, TEXT("PATH IS EMPTY"));
		return EBTNodeResult::Failed;
	}
	
	
	//Debug log only
	FString ConcatenatedNames;
	for (AA_WaypointActor* wp : Path)
	{
		ConcatenatedNames += wp->pointName + TEXT("->"); // Add the waypoint name and a comma-space separator
	}
	GEngine->AddOnScreenDebugMessage(5, 10.f, FColor::Green, FString::Printf(TEXT("Path: %s"), *ConcatenatedNames));



	// - - - - - - - - - - - - - - - - - - - - - - - - - - Movement logic here!!!! - - - - - - - - - - - - - - - - - - - - - - - - - - -
	// Too tired to do it now
	UNewCustomPathArray* CustomWaypointArray = NewObject<UNewCustomPathArray>();
	CustomWaypointArray->ArrayPath = Path;
	
	Blackboard->SetValueAsObject(TEXT("PathToTarget"), CustomWaypointArray);
	
	// Store the resulting path in the blackboard
	//Blackboard->SetValueAsBool(TEXT("pathfindingReady"), false);
	return EBTNodeResult::Succeeded;
}

FString UN_BTTask_PathfinderExperimental::GetStaticDescription() const
{
	return FString::Printf(TEXT("Roam behaviour, or maybe it's not..."));
}
