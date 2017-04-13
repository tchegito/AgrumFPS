// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "Player/BasePlayerController.h"
#include "World/BaseWorldSettings.h"
#include "TacticalOpsGameModeBase.generated.h"

// Struct to store information about teams
USTRUCT()
struct FTeamStruct
{
	GENERATED_BODY()
		// Thumbnail for this team used in customization
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = TeamSettings)
		UTexture2D * teamThumbnail;

	// Get ammunition for HUD
	UPROPERTY(EditDefaultsOnly, Category = TeamSettings)
		 int32 GetAmmunition;
		
};



UCLASS()
class TACTICALOPS_API ATacticalOpsGameModeBase : public AGameMode
{
	GENERATED_BODY()

public:
	// Constructor
	ATacticalOpsGameModeBase(const FObjectInitializer & ObjectInitializer);

	virtual void InitGameState() override;

	virtual void PostLogin(APlayerController * NewPlayer) override;

	virtual void BeginPlay()override;
	//*************************************************************************************************
		//on définit les temps de jeux et de round et le nombre de team
	UPROPERTY(EditAnywhere, Category = GameSettings)
		int32 GameTime;

	UPROPERTY(EditAnywhere, Category = GameSettings)
		int32 RoundTime;

	UPROPERTY(EditAnywhere, Category = GameSettings)
		int32 PreRoundTime;
	
	UPROPERTY(EditAnywhere, Category = GameSettings)
		int32 PostRoundTime;

	UPROPERTY(EditAnywhere, Category = GameSettings)
		int32 NumTeams;
	
	UPROPERTY(EditAnywhere, Category = TeamSettings)
		ESpecialForcesTeamEnum SFTeam;

	UPROPERTY(EditAnywhere, Category = TeamSettings)
		ETerroTeamEnum TerrosTeam;
	//******************************************************************************************************
	//EndGame mechanics

	// Called when match time expired
	void OnGameTimeExpired();

	// Ends this match, no team wins
	virtual void EndMatch() override;

	// End the match with specified winner team
	void EndMatch(ETeamGalEnum WinnerTeam);

	//bool pour déterminer si le temps de jeu est fini
	bool bGameOver;


	//******************************************************************************************************
	//On définit le gagnant du round par défaut
	UPROPERTY(EditAnywhere, Category = TeamSettings)
		ETeamGalEnum DefaultWinner;

	//******************************************************************************************************
	//Round Mechanics

	//quand le temps de round est écoulé pour changer d'etat de round :preround,progress,postround
	virtual void OnRoundTimeExpired();

	//
	void RoundTimeExpired();

	// Setup everything for a new round, e.g. reset the level
	
	virtual void NextRound();

	void StartRound();

	void EndRound(ETeamGalEnum RoundWinner);

	virtual void Reset() override;

	UPROPERTY( BlueprintReadOnly, Category = GameState)
		ERoundStateEnum RoundState;

	//******************************************************************************************************
	UPROPERTY(EditAnywhere, Category = GameState)
	bool CanSpawn;

	// Will move a player to the correct state after login
	virtual void MovePlayerToEntryState(ABasePlayerController * PC);

	// Move all player controllers to NewState
	void MoveAllPlayersToState(EPlayerStateEnum NewState);
	
	UPROPERTY(EditAnywhere, Category = GameState)
	FTeamStruct TerroTeam;


	// Broadcast chat message to all clients
	void BroadcastChatMessage(ABasePlayerController * FromPC, const FString & Message, bool bTeamOnly);

public:
	// Player wants to spawn
	void PlayerSpawn(ABasePlayerController * PC);

	// Overrideable, return whether player may spawn
	virtual bool CanPlayerSpawn(ABasePlayerController * PC) const;
	// Player wants to join a team

	void PlayerJoinTeam(ABasePlayerController * PC, ETeamGalEnum InTeam);
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
};
