// Fill out your copyright notice in the Description page of Project Settings.

#include "TacticalOps.h"
#include "UnrealNetwork.h"
#include "Game/MyGameStateBase.h"
#include "Player/BasePlayerController.h"
#include "TacticalOpsGameModeBase.h"





ATacticalOpsGameModeBase::ATacticalOpsGameModeBase(const FObjectInitializer & ObjectInitializer)
{

	GameStateClass = AMyGameStateBase::StaticClass();
	DefaultPawnClass = NULL;
	SpectatorClass = NULL;

	GameTime = 1200;
	RoundTime = 240;
	PreRoundTime = 5;
	PostRoundTime = 5;
	bGameOver = false;

	NumTeams = 2;
	TerrosTeam = ETerroTeamEnum::Default;
	SFTeam = ESpecialForcesTeamEnum::Default;


	RoundState = ERoundStateEnum::PreRound;
	
	
	CanSpawn = true;
}

//************************************************************************************************************************


void ATacticalOpsGameModeBase::InitGameState  ()
{
	Super::InitGameState();

	AMyGameStateBase *TOGameState = Cast<AMyGameStateBase>(GameState);
	if (TOGameState)
	{
		TOGameState->TimeRemaining = GameTime;
		TOGameState->RoundTimeRemaining = PreRoundTime;
	
		//Scores et nombre de round à 0
		TOGameState->ResetScores();
		StartRound();

	}
}



void ATacticalOpsGameModeBase::PostLogin(APlayerController * NewPlayer)
{
	Super::PostLogin(NewPlayer);

	ABasePlayerController * PC = Cast<ABasePlayerController>(NewPlayer);
	if (PC)
	{
		if (HasMatchEnded())
		{
			PC->EnterMatchEndState();
		}
		else
		{
			PC->EnterTeamSelectionState(); 
				
			
		}

		BroadcastChatMessage(PC, TEXT("Connected"), false);
	
}
}
void ATacticalOpsGameModeBase::BeginPlay()
{
	Super::BeginPlay();

}

//******************************************************************************************************
//EndGame mechanics

void ATacticalOpsGameModeBase :: OnGameTimeExpired()
{
	switch (RoundState)
	{
	case (ERoundStateEnum::PreRound):
	//StopGameTimer et continuer le round
		break;

	case (ERoundStateEnum::InProgress):
		//StopGameTimer et finir le round
		break;

	case (ERoundStateEnum::RoundEnd):
		EndMatch();
		break;
	}
}

void ATacticalOpsGameModeBase ::EndMatch()
{

}

void ATacticalOpsGameModeBase::EndMatch(ETeamGalEnum WinnerTeam)
{

}

//******************************************************************************************************
//Round Mechanics


void ATacticalOpsGameModeBase::OnRoundTimeExpired()
{
	switch (RoundState)
	{
	case (ERoundStateEnum::PreRound):
		StartRound();
		break;

	case (ERoundStateEnum::InProgress):
		RoundTimeExpired();
		break;

	case (ERoundStateEnum::RoundEnd):
		NextRound();
		break;
	}

}

//le round se termine et on passe en postRound
void ATacticalOpsGameModeBase::RoundTimeExpired()
{
	RoundState = ERoundStateEnum::RoundEnd;
	AMyGameStateBase *TOGameState = Cast<AMyGameStateBase>(GameState);
	TOGameState->RoundTimeRemaining = PostRoundTime;
}

//pre round terminé on lance le round
void ATacticalOpsGameModeBase::StartRound()
{
	RoundState = ERoundStateEnum::InProgress;

	AMyGameStateBase *TOGameState = Cast<AMyGameStateBase>(GameState);
	TOGameState->RoundTimeRemaining = RoundTime;

}
// post round terminé, on lance préround
void ATacticalOpsGameModeBase::NextRound()
{
	RoundState = ERoundStateEnum::PreRound;

	AMyGameStateBase *TOGameState = Cast<AMyGameStateBase>(GameState);
	if (bGameOver)
	{
		EndMatch();
	}

	else
	{
		TOGameState->RoundTimeRemaining = PreRoundTime;
		TOGameState->RoundPlayed++;
	}
	
		
}


void ATacticalOpsGameModeBase::EndRound(ETeamGalEnum RoundWinner)
{
	if (RoundState ==ERoundStateEnum::InProgress)
	{
		RoundState = ERoundStateEnum::RoundEnd;
		AMyGameStateBase *TOGameState = Cast<AMyGameStateBase>(GameState);
		TOGameState->RoundTimeRemaining = PostRoundTime;
	}

}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ATacticalOpsGameModeBase::BroadcastChatMessage(ABasePlayerController * FromPC, const FString & Message, bool bTeamOnly)
{/*
	ABasePlayerState * FromPS = Cast<ABasePlayerState>(FromPC->PlayerState);
	for (FConstPlayerControllerIterator PlayerItr = GetWorld()->GetPlayerControllerIterator(); PlayerItr; ++PlayerItr)
	{
		ABasePlayerController * PC = Cast<ABasePlayerController>(*PlayerItr);
		if (CanPlayerReceiveChatMessage(FromPC, PC, bTeamOnly))
		{
			PC->ClientReceiveChatMessage(Message, FromPS);
		}
	}
	*/
}