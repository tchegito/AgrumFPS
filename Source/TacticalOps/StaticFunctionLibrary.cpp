// Fill out your copyright notice in the Description page of Project Settings.

#include "TacticalOps.h"
#include "StaticFunctionLibrary.h"




UBaseGameInstance * UStaticFunctionLibrary::GetBaseGameInstance(const UObject * WorldContextObject)
{
	UWorld * World = GEngine->GetWorldFromContextObject(WorldContextObject);
	if (World)
	{
		return Cast<UBaseGameInstance>(World->GetGameInstance());
	}

	return NULL;
}