// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALOPS_API AMyGameStateBase : public AGameState
{
	GENERATED_BODY()
public:
	AMyGameStateBase();

		// Remaining time seconds for the match/round
	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
	int32 TimeRemaining;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
	int32 RoundTimeRemaining;
	
	void DefaultTimer() override;
	
	FTimerHandle RoundTimer;
	virtual void BeginPlay()override;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//round déja joué et round gagné par les différentes teams
	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
		int32 RoundPlayed;

	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
		int32 TeamARoundsWon;
	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
		int32 TeamBRoundsWon;


	//on remet à 0 le nombre de rounds, et les scores
	void ResetScores();



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
	int32 NumTeam;

	//nombre de sous team terros
	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
	int32 NumTerrosTeam;
	
	//nombre de sous team SF
	UPROPERTY(Replicated, BlueprintReadOnly, Category = GameState)
	int32 NumSpecialForceTeam;
};
