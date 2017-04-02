// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "UnrealNetwork.h"
#include "TacticalOps.h"
#include "BasePlayerController.generated.h"

/**
 * 
 */
UENUM()
enum class EPlayerStateEnum : uint8
{
	None,
	TeamSelection,
	Spawn,
	Playing,
	Death,
	Spectating,
	MatchEnd,
};

UCLASS()
class TACTICALOPS_API ABasePlayerController : public APlayerController
{
	GENERATED_BODY()
public:	
		ABasePlayerController();

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Current state of this player controller, replicated
	UPROPERTY(ReplicatedUsing = OnRep_State)
		EPlayerStateEnum State;

	UFUNCTION()
		void OnRep_State();

	// Change states
	void EnterTeamSelectionState();

	void EnterSpawnState();

	void EnterPlayingState();

	void EnterDeathState();

	void EnterSpectatingState();

	void EnterMatchEndState();


private:
	// State change notification events, executed on owning client
	void OnEnterTeamSelectionState();

	void OnEnterSpawnState();

	void OnEnterPlayingState();

	void OnEnterDeathState();

	void OnEnterSpectatingState();

	void OnEnterMatchEndState();

	void OnEnterState(TSubclassOf<AHUD> HUDClass, bool bMouseEnabled);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Set view target to camera actor selected in world settings
protected:
	void SetViewTargetToMenuCamera();


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Try to join team
	UFUNCTION(BlueprintCallable, Category = PlayerController)
		void JoinTeam(ETeamGalEnum InTeam);

private:
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerJoinTeam(ETeamGalEnum InTeam);

public:
	// Try to spawn
	UFUNCTION(BlueprintCallable, Category = PlayerController)
		void Spawn();


private:
	UFUNCTION(Server, Reliable, WithValidation)
		void ServerSpawn();
};
