// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "A_WaypointActor.h"
#include "A_PathfindingManager.generated.h"


UCLASS()
class KAIJUGAMETEST_API AA_PathfindingManager : public AActor
{
	GENERATED_BODY()
	
public:	
	AA_PathfindingManager();//Constructor
	//static AA_PathfindingManager* PFMInstance;//Singleton insane
	
	UPROPERTY(BlueprintReadWrite, Category = "Pathfinding")
	TArray<AA_WaypointActor*> AllWaypoints;
	

	void FindAllWaypoints();//Get wayppoints in scenn
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//static AA_PathfindingManager* GetInstance();//Getter for singleton: these messages keep my mind on track
	
	UFUNCTION(BlueprintCallable, Category = "Pathfinding")
	TArray<AA_WaypointActor*> FindPath(AA_WaypointActor* StartWaypoint, AA_WaypointActor* TargetWaypoint);

};
