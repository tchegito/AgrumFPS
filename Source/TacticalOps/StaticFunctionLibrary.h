// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Game/BaseGameInstance.h"
#include "StaticFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALOPS_API UStaticFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
	
		UFUNCTION(BlueprintPure, Category = StaticFunctionLibrary, Meta = (WorldContext = WorldContextObject))
		static UBaseGameInstance * GetBaseGameInstance(const UObject * WorldContextObject);
};
