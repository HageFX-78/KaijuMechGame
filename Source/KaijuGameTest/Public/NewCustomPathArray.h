// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "A_WaypointActor.h"
#include "NewCustomPathArray.generated.h"

/**
 * 
 */
UCLASS(Blueprintable, BlueprintType)
class KAIJUGAMETEST_API UNewCustomPathArray : public UObject
{
	GENERATED_BODY()
public:
    UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category="Default")
    TArray<AA_WaypointActor*> ArrayPath;
};
