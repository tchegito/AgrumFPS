// Fill out your copyright notice in the Description page of Project Settings.

#include "TacticalOps.h"
#include "TeamSelectionHUD.h"




ATeamSelectionHUD::ATeamSelectionHUD()
{
	static ConstructorHelpers::FObjectFinder<UObject> NewMainWidgetClass(TEXT("WidgetBlueprint'/Game/UI/TeamSelection_Widget.TeamSelection_Widget'"));
	MainWidgetClass = (UClass*)NewMainWidgetClass.Object;
}