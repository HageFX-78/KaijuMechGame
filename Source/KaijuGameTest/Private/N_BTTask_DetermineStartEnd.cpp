// Fill out your copyright notice in the Description page of Project Settings.


#include "N_BTTask_DetermineStartEnd.h"

#include "AIController.h"

#include "A_WaypointActor.h"
#include "NavigationSystem.h"
#include "NetworkMessage.h"
#include "BehaviorTree/BlackboardComponent.h"

UN_BTTask_DetermineStartEnd::UN_BTTask_DetermineStartEnd()
{
	NodeName = TEXT("Location/Destination Check");
}


AA_WaypointActor* FindRandomWaypoint(TArray<AA_WaypointActor*> AllWp, AA_WaypointActor* CloseWp);


EBTNodeResult::Type UN_BTTask_DetermineStartEnd::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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

	FTransform AITransform = ((OwnerComp.GetAIOwner())->GetPawn())->GetActorTransform();
	float MinDistanceSq = MAX_FLT;
	AA_WaypointActor* ClosestWaypoint = nullptr;
	
	for (AA_WaypointActor* Waypoint : PFMan->AllWaypoints)
	{
		FVector WaypointLocation = Waypoint->GetActorLocation();
		float DistanceSq = FVector::DistSquared(AITransform.GetLocation(), WaypointLocation);
		
		if (DistanceSq < MinDistanceSq)
		{
			MinDistanceSq = DistanceSq;
			ClosestWaypoint = Waypoint;
		}
	}
	
	Blackboard->SetValueAsObject(TEXT("ClosestPoint"), ClosestWaypoint);
	Blackboard->SetValueAsObject(TEXT("StartWaypoint"), ClosestWaypoint);//Now is intended to be the same, need to check in the future
	Blackboard->SetValueAsObject(TEXT("TargetWaypoint"), FindRandomWaypoint(PFMan->AllWaypoints, ClosestWaypoint));

	
	return EBTNodeResult::Succeeded;
}

AA_WaypointActor* FindRandomWaypoint(TArray<AA_WaypointActor*> AllWp, AA_WaypointActor* CloseWp)
{
	int32 RandomIndex = FMath::RandRange(0, AllWp.Num() - 1);
	
	AA_WaypointActor* RandomTargetWaypoint = AllWp[RandomIndex];

	if(RandomTargetWaypoint == CloseWp)
	{
		return FindRandomWaypoint(AllWp, CloseWp);
	}
	else
	{
		return RandomTargetWaypoint;
	}
	
}


FString UN_BTTask_DetermineStartEnd::GetStaticDescription() const
{
	return FString::Printf(TEXT("Determine start position and end position"));
}
