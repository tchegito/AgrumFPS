// Fill out your copyright notice in the Description page of Project Settings.

#include "TacticalOps.h"
#include "UnrealNetwork.h"
#include "TOPlayerState.h"



ATOPlayerState::ATOPlayerState()
{
	TeamNumber = ETeamKindEnum::None;

	NumKills = 0;
	NumDeaths = 0;
	TeamMateKilled = 0;

	NumBulletsFired = 0;
	NumShotFired = 0;
	NumFiredTarget = 0;
	NumShotTarget = 0;
}


void ATOPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ATOPlayerState, NumKills);
	DOREPLIFETIME(ATOPlayerState, NumDeaths);
	//DOREPLIFETIME(ATOPlayerState, Team);
	DOREPLIFETIME(ATOPlayerState, TeamMateKilled);
	//accuracy
	DOREPLIFETIME(ATOPlayerState, NumBulletsFired);
	DOREPLIFETIME(ATOPlayerState, NumShotFired);
	DOREPLIFETIME(ATOPlayerState, NumFiredTarget);
	DOREPLIFETIME(ATOPlayerState, NumShotTarget);
}

void ATOPlayerState::Reset()
{
	Super::Reset();

	//PlayerStates persist across seamless travel.  Keep the same teams as previous match.
	//SetTeamNum(0);
	NumKills = 0;
	NumDeaths = 0;
	TeamMateKilled = 0;
	NumBulletsFired = 0;
	NumShotFired = 0;
	NumFiredTarget = 0;
	NumShotTarget = 0;
}

////////////////////////////////////////////////////////////////////////////////////////
void ATOPlayerState::SetTeam(ETeamKindEnum NewTeam)
{
	TeamNumber = NewTeam;
}

/*
int32 ATOPlayerState::GetTeamNum() const
{
	return TeamNumber;
}
*/
//////////////////////////////////////////////////////////////////////////////////////////////////
void ATOPlayerState::AddBulletsFired(int32 NumBullets)
{
	NumBulletsFired += NumBullets;
}

void ATOPlayerState::AddBshotsFired(int32 NumShots)
{
	NumShotFired += NumShots;
}


void ATOPlayerState::AddBulletTarget(int32 NumBullets)
{
	NumFiredTarget += NumBullets;
}

void ATOPlayerState::AddBshotsTarget(int32 NumShots)
{
	NumShotTarget += NumShots;
}

//////////////////////////////////////////////////////////////////////////////////////////////////

int32 ATOPlayerState::GetKills() const
{
	return NumKills;
}

int32 ATOPlayerState::GetDeaths() const
{
	return NumDeaths;
}

int32 ATOPlayerState::GetTeamKilled() const
{
	return TeamMateKilled;
}

