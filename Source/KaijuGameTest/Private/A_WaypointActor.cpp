// Fill out your copyright notice in the Description page of Project Settings.


#include "A_WaypointActor.h"

// Sets default values
AA_WaypointActor::AA_WaypointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;
	
	SpriteComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("SpriteComponent"));
	SpriteComponent->SetupAttachment(RootComponent);//Set as child of root

	SpriteComponent->SetWorldScale3D(FVector(10.f, 10.f, 10.f));
	SpriteComponent->SetHiddenInGame(true);
}

// Called when the game starts or when spawned
void AA_WaypointActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AA_WaypointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

