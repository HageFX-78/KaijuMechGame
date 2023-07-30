// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "A_WaypointActor.h"
#include "CustomPathArray.generated.h"

/** Custom array object so i can store it as a singular object containing an array int he blackboard
 * this is why i hate unreal
 * 
 */
UCLASS()
class KAIJUGAMETEST_API UCustomPathArray : public UObject
{
	GENERATED_BODY()
public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Default")
	TArray<AA_WaypointActor*> ArrayPath;
};
