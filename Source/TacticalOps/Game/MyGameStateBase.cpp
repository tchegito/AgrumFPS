// Fill out your copyright notice in the Description page of Project Settings.

#include "TacticalOps.h"
#include "UnrealNetwork.h"
#include "TacticalOpsGameModeBase.h"
#include "MyGameStateBase.h"


 AMyGameStateBase::AMyGameStateBase()
{
	NumTeam = 0;
	RoundPlayed = 0;
	TimeRemaining = 0;
	RoundTimeRemaining = 0;
	TeamARoundsWon = 0;
	TeamBRoundsWon = 0;
	NumSpecialForceTeam = 1;
	NumTerrosTeam = 1;
}
 void AMyGameStateBase::BeginPlay()
 {
	 Super::BeginPlay();

 }

void AMyGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMyGameStateBase, RoundTimeRemaining);
	DOREPLIFETIME(AMyGameStateBase, TimeRemaining);
	DOREPLIFETIME(AMyGameStateBase, RoundPlayed);
	DOREPLIFETIME(AMyGameStateBase, TeamARoundsWon);
	DOREPLIFETIME(AMyGameStateBase, TeamBRoundsWon);
	
	DOREPLIFETIME(AMyGameStateBase, NumTeam);
	DOREPLIFETIME(AMyGameStateBase, NumTerrosTeam);
	DOREPLIFETIME(AMyGameStateBase, NumSpecialForceTeam);
}



void AMyGameStateBase::DefaultTimer()
{
	Super::DefaultTimer();
	
	ATacticalOpsGameModeBase * FPSGameMode = Cast<ATacticalOpsGameModeBase>(GetWorld()->GetAuthGameMode());
	

	if (IsMatchInProgress() && TimeRemaining > 0)
	{
		TimeRemaining--;
		if (TimeRemaining == 0)
		{
			
			if (FPSGameMode)
			{
				// Notify game mode that match timed out
				FPSGameMode->OnGameTimeExpired();
				FPSGameMode->bGameOver = true;
			}
		}
		
	}
	if (FPSGameMode->RoundState == ERoundStateEnum::InProgress &&RoundTimeRemaining > 0)
	{
		RoundTimeRemaining--;
	
		if (RoundTimeRemaining ==0)
		{
			//FPSGameMode->OnRoundTimeExpired;
		}
	
	}

}

void AMyGameStateBase::ResetScores()
{
	RoundPlayed = 0;
	TeamARoundsWon = 0;
	TeamBRoundsWon = 0;
}

/*
RoundTimer
RoundTimeRemaining--;
if (RoundTimeRemaining == 0)
{
	ATacticalOpsGameModeBase * FPSGameMode = Cast<ATacticalOpsGameModeBase>(GetWorld()->GetAuthGameMode());
	FPSGameMode->OnRoundTimeExpired();

}
*/