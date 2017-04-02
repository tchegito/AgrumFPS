// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameModeBase.h"
#include "Player/BasePlayerController.h"
#include "TacticalOpsGameModeBase.generated.h"

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
	virtual void EndMatch() ;

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

	

	UPROPERTY( BlueprintReadOnly, Category = GameState)
		ERoundStateEnum RoundState;
	//******************************************************************************************************
	UPROPERTY(EditAnywhere, Category = GameState)
	bool CanSpawn;
	
	UPROPERTY(EditAnywhere, Category = GameState)
	FTeamStruct TerroTeam;


	// Broadcast chat message to all clients
	void BroadcastChatMessage(ABasePlayerController * FromPC, const FString & Message, bool bTeamOnly);
};
