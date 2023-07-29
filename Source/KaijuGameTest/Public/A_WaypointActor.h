// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BillboardComponent.h"
#include "A_WaypointActor.generated.h"


USTRUCT(BlueprintType)
struct FWaypointConnection//Struct for each connection to waypoints with state to see if is blocked
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	AA_WaypointActor* ConnectedWaypoint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	bool bIsRoadBlocked = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	int distanceWeighted = 1;//Default 1 for now
};

UCLASS()
class KAIJUGAMETEST_API AA_WaypointActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AA_WaypointActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	int nodeID;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	TArray<FWaypointConnection> ConnectedWaypoints;//Waypoints connected to this specific node
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pathfinding")
	FString pointName = "default_name";//Waypoints connected to this specific node

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pathfinding")
	class USceneComponent* DefaultSceneRoot; // Declaration of DefaultSceneRoot component
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Pathfinding")
	class UBillboardComponent* SpriteComponent;

};
