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
	Super::EndMatch();

	// Transition all players to match end state
	MoveAllPlayersToState(EPlayerStateEnum::MatchEnd);

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
	if (bGameOver)
	{
		EndMatch();
	}
	
	else
	{
		RoundState = ERoundStateEnum::PreRound;
		Reset();

	AMyGameStateBase *TOGameState = Cast<AMyGameStateBase>(GameState);
	

	
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

void ATacticalOpsGameModeBase::Reset()
{
	// Do nothing
}

void ATacticalOpsGameModeBase::MovePlayerToEntryState(ABasePlayerController * PC)
{
	PC->EnterSpawnState();
}


void ATacticalOpsGameModeBase::MoveAllPlayersToState(EPlayerStateEnum NewState)
{
	// Save enter state function pointer so we don't have to do the switch for every player
	typedef void (ABasePlayerController::*FunctionPtr)(void);
	FunctionPtr Function = &ABasePlayerController::EnterSpectatingState;
	switch (NewState)
	{
	case (EPlayerStateEnum::TeamSelection):
		Function = &ABasePlayerController::EnterTeamSelectionState;
		break;
	case (EPlayerStateEnum::Spawn):
		Function = &ABasePlayerController::EnterSpawnState;
		break;
	case (EPlayerStateEnum::Playing):
		Function = &ABasePlayerController::EnterPlayingState;
		break;
	case (EPlayerStateEnum::Death):
		Function = &ABasePlayerController::EnterDeathState;
		break;
	case (EPlayerStateEnum::Spectating):
		Function = &ABasePlayerController::EnterSpectatingState;
		break;
	case (EPlayerStateEnum::MatchEnd):
		Function = &ABasePlayerController::EnterMatchEndState;
		break;
	}

	for (FConstPlayerControllerIterator PlayerItr = GetWorld()->GetPlayerControllerIterator(); PlayerItr; ++PlayerItr)
	{
		ABasePlayerController * PC = Cast<ABasePlayerController>(*PlayerItr);
		if (PC)
		{
			(PC->*Function)();
		}
	}
}


void ATacticalOpsGameModeBase::PlayerSpawn(ABasePlayerController * PC)
{
	if (CanPlayerSpawn(PC))
	{
		AActor * PlayerStart = FindPlayerStart(PC);
		if (PlayerStart)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

			// Spawn soldier
			ASoldier * Soldier = GetWorld()->SpawnActor<ASoldier>(SoldierClass, PlayerStart->GetActorLocation(), FRotator(0.f, PlayerStart->GetActorRotation().Yaw, 0.f), SpawnParams);
			if (Soldier)
			{
				USkeletalMesh * SoldierMesh = NULL;
				ABaseWorldSettings * WorldSettings = Cast<ABaseWorldSettings>(GetWorldSettings());
				if (WorldSettings)
				{
					const ETeamEnum PlayerTeam = PC->GetTeam();
					const bool bTeamAMeshes = PlayerTeam == ETeamEnum::TeamA || PlayerTeam == ETeamEnum::None;
					const TArray<USkeletalMesh *> & MeshesArray = bTeamAMeshes ? WorldSettings->TeamASoldierMeshes : WorldSettings->TeamBSoldierMeshes;
					if (WorldSettings->bUseRandomSoldierMeshes)
					{
						if (MeshesArray.Num())
							SoldierMesh = MeshesArray[FMath::RandRange(0, MeshesArray.Num() - 1)];
					}
					else
					{
						const uint8 LoadoutSlot = PC->GetLoadoutSlot();
						if (MeshesArray.IsValidIndex(LoadoutSlot))
							SoldierMesh = MeshesArray[LoadoutSlot];
					}
				}

				Soldier->SetLoadout(GetPlayerLoadout(PC), SoldierMesh);
				PC->Possess(Soldier);
				PC->EnterPlayingState();
			}
		}
	}
}