// Fill out your copyright notice in the Description page of Project Settings.


#include "A_PathfindingManager.h"
#include "Kismet/GameplayStatics.h"


AA_PathfindingManager::AA_PathfindingManager()// COnstructor
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}
// Called when the game starts or when spawned
void AA_PathfindingManager::BeginPlay()
{
	Super::BeginPlay();
	FindAllWaypoints();

	
}
//Default tick, Update from unity pretty much
void AA_PathfindingManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// ============================== My functions ===========================================
void AA_PathfindingManager::FindAllWaypoints()//Find all waypoints to reference at start
{
	// Use GetAllActorsOfClass to find all waypoints in the level
	TArray<AActor*> FoundWaypoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AA_WaypointActor::StaticClass(), FoundWaypoints);

	// Store references to the waypoints in the Waypoints array
	for (AActor* wp : FoundWaypoints)
	{
		AA_WaypointActor* thisWaypoint = Cast<AA_WaypointActor>(wp);
		if (thisWaypoint)
		{
			AllWaypoints.Add(thisWaypoint);
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("Added a waypoint with count: %d"), AllWaypoints.Num()));
		}
	}
}


//Findpath to be called from Player and Kaiju
TArray<AA_WaypointActor*> AA_PathfindingManager::FindPath(AA_WaypointActor* StartWaypoint,
	AA_WaypointActor* TargetWaypoint)
{
	TArray<AA_WaypointActor*> resultPath;

	TMap<AA_WaypointActor*, int> DistanceMap;
	
	TMap<AA_WaypointActor*, AA_WaypointActor*> ParentMap;
	
	for (AA_WaypointActor* thisWp : AllWaypoints)
	{
		GEngine->AddOnScreenDebugMessage(7, 2.f, FColor::Purple, TEXT("Added distance and parrent map"));
		DistanceMap.Add(thisWp, 999999);
		ParentMap.Add(thisWp, nullptr);
	}
	// ***** DEBUG

	if(AllWaypoints.Num() == 0)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, TEXT("NO WAYPOINTS WTF"));
		return TArray<AA_WaypointActor*>();
	}	
	if(DistanceMap.Num() == 0)
	{
		return TArray<AA_WaypointActor*>();
	}
	
	
	DistanceMap[StartWaypoint] = 0;

	// Create an empty set to keep record all visited waypoints
	TSet<AA_WaypointActor*> VisitedWaypoints;

	// Main loop for Dijkstra's algorithm
	while (VisitedWaypoints.Num() < AllWaypoints.Num())
	{
		// Find the waypoint with the smallest distance that has not been visited
		AA_WaypointActor* CurrentWaypoint = nullptr;
		float MinDistance = 999999;//From big to small, reminder to self at 3am
		for (AA_WaypointActor* thisWaypoint : AllWaypoints)
		{
			if (!VisitedWaypoints.Contains(thisWaypoint) && DistanceMap[thisWaypoint] < MinDistance)
			{
				CurrentWaypoint = thisWaypoint;
				MinDistance = DistanceMap[thisWaypoint];
			}
		}

		// If we didn't find a valid waypoint, break the loop
		if (!CurrentWaypoint)
		{
			GEngine->AddOnScreenDebugMessage(10, 5.f, FColor::White, TEXT("Cant seem to find path or smtg broke"));
			break;
		}

		// Mark the current waypoint as visited
		VisitedWaypoints.Add(CurrentWaypoint);

		// Update distances and parents for adjacent waypoints
		for (FWaypointConnection connectionStruct : CurrentWaypoint->ConnectedWaypoints)
		{
			AA_WaypointActor* theConnectedWaypoint = connectionStruct.ConnectedWaypoint;//Singular
			float NewDistance = DistanceMap[CurrentWaypoint] + 1.0f; // In this example, assume all connections have the same weight (1.0f)

			if (NewDistance < DistanceMap[theConnectedWaypoint])
			{
				DistanceMap[theConnectedWaypoint] = NewDistance;
				ParentMap[theConnectedWaypoint] = CurrentWaypoint;
			}
		}
	}

	// Get parent->parent->parent of defined path from the target
	AA_WaypointActor* tPoint = TargetWaypoint;
	while (tPoint != nullptr)
	{
		resultPath.Insert(tPoint, 0);//First goes all the way back
		tPoint = ParentMap[tPoint];
	}
	GEngine->AddOnScreenDebugMessage(10, 5.f, FColor::White, TEXT("Path returned!"));
	return resultPath;
}

