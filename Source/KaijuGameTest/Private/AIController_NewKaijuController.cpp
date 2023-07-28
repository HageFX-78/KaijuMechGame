// Fill out your copyright notice in the Description page of Project Settings.


#include "AIController_NewKaijuController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "CoreUObject/Internal/UObject/LinkerLoadImportBehavior.h"

AAIController_NewKaijuController::AAIController_NewKaijuController()
{
	BehaviourTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behaviour Tree Component"));
	BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
}

void AAIController_NewKaijuController::BeginPlay()
{
	Super::BeginPlay();

	if(IsValid(BehaviourTree.Get()))
	{
		RunBehaviorTree(BehaviourTree.Get());
		BehaviourTreeComponent->StartTree(*BehaviourTree.Get());
	}
	
}

void AAIController_NewKaijuController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if(IsValid(Blackboard.Get()) && IsValid(BehaviourTree.Get()))
	{
		Blackboard->InitializeBlackboard(*BehaviourTree.Get()->BlackboardAsset.Get());
	}
	
}
