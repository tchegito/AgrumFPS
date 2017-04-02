// Fill out your copyright notice in the Description page of Project Settings.

#include "TacticalOps.h"
#include "UnrealNetwork.h"
#include "Hud/TeamSelectionHUD.h"
#include "World/BaseWorldSettings.h"
#include "TacticalOpsGameModeBase.h"
#include "BasePlayerController.h"


ABasePlayerController ::ABasePlayerController()
{

}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ABasePlayerController::OnRep_State()
{
	switch (State)
	{
	case (EPlayerStateEnum::TeamSelection):
		OnEnterTeamSelectionState();
		break;
	case (EPlayerStateEnum::Spawn):
		OnEnterSpawnState();
		break;
	case (EPlayerStateEnum::Playing):
		OnEnterPlayingState();
		break;
	case (EPlayerStateEnum::Death):
		OnEnterDeathState();
		break;
	case (EPlayerStateEnum::Spectating):
		OnEnterSpectatingState();
		break;
	case (EPlayerStateEnum::MatchEnd):
		OnEnterMatchEndState();
		break;
	}
}

//permet de d�finir l'�tat du joueur en selection d'�quipe
void ABasePlayerController::EnterTeamSelectionState()
{
	State = EPlayerStateEnum::TeamSelection;

	if (IsLocalController())
	{
		OnEnterTeamSelectionState();
	}
}


void ABasePlayerController::EnterSpawnState()
{
	State = EPlayerStateEnum::Spawn;

	if (IsLocalController())
	{
		OnEnterSpawnState();
	}
}

void ABasePlayerController::EnterPlayingState()
{
	State = EPlayerStateEnum::Playing;

	if (IsLocalController())
	{
		OnEnterPlayingState();
	}
}

void ABasePlayerController::EnterDeathState()
{
	State = EPlayerStateEnum::Death;

	BeginInactiveState();

	if (IsLocalController())
	{
		OnEnterDeathState();
	}
}

void ABasePlayerController::EnterSpectatingState()
{
	State = EPlayerStateEnum::Spectating;

	if (IsLocalController())
	{
		OnEnterSpectatingState();
	}
}

void ABasePlayerController::EnterMatchEndState()
{
	State = EPlayerStateEnum::MatchEnd;

	// Unpossess current pawn
	UnPossess();
	

	if (IsLocalController())
	{
		OnEnterMatchEndState();
	}
}

void ABasePlayerController::OnEnterTeamSelectionState()
{
	OnEnterState(ATeamSelectionHUD::StaticClass(), true);
	SetViewTargetToMenuCamera();
}

void ABasePlayerController::OnEnterSpawnState()
{

}

void ABasePlayerController::OnEnterPlayingState()
{

}

void ABasePlayerController::OnEnterDeathState()
{

}

void ABasePlayerController::OnEnterSpectatingState()
{

}

void ABasePlayerController::OnEnterMatchEndState()
{

}


void ABasePlayerController::OnEnterState(TSubclassOf<AHUD> HUDClass, bool bMouseEnabled)
{


}

void ABasePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ABasePlayerController, State);
}


void ABasePlayerController::SetViewTargetToMenuCamera()
{
	ABaseWorldSettings * WorldSettings = Cast<ABaseWorldSettings>(GetWorld()->GetWorldSettings());
	if (WorldSettings && WorldSettings->MenuCameras.Num() > 0 && !WorldSettings->MenuCameras.Contains(GetViewTarget()))
	{
		SetViewTarget(WorldSettings->MenuCameras[FMath::RandRange(0, WorldSettings->MenuCameras.Num() - 1)]);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Spawn and Teamjoin Mechanics


void ABasePlayerController::JoinTeam(ETeamGalEnum InTeam)
{
	if (GetNetMode() == NM_Client)
	{
		ServerJoinTeam(InTeam);
		return;
	}

	AGameModeBase * GameMode = Cast<AGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->PlayerJoinTeam(this, InTeam);
	}
}

void ABasePlayerController::ServerJoinTeam(ETeamGalEnum InTeam)
{
	JoinTeam(InTeam);
}

void ABasePlayerController::Spawn()
{
	if (GetNetMode() == NM_Client)
	{
		

		ServerSpawn();
		return;
	}

	ATacticalOpsGameModeBase * GameMode = Cast<ATacticalOpsGameModeBase>(GetWorld()->GetAuthGameMode());
	if (GameMode)
	{
		GameMode->PlayerSpawn(this);
	}
}

void ABasePlayerController::ServerSpawn()
{
	Spawn();
}

