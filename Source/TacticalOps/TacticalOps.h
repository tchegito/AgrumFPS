// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"

/**
*
*/
UENUM(BlueprintType)
enum class ERoundStateEnum : uint8
{
	PreRound,
	InProgress,
	RoundEnd,
};


UENUM(BlueprintType)
enum class ETeamGalEnum : uint8
{
	None,
	Terros,
	SpecialOps,
};

UENUM(BlueprintType)
enum class ETerroTeamEnum : uint8
{
	Default,
	SentierLumineux,
	Jambon,
};


UENUM(BlueprintType)
enum class ESpecialForcesTeamEnum : uint8
{
	Default,
	SWAT,
	Spetnaz,
	GIGN,
};
