// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "TOPlayerState.generated.h"





UENUM(BlueprintType)
enum class ETeamKindEnum : uint8
{
None,
Terros,
SpecialForces,
Jambon,
SentierLumineux,
GIGN,
Spetnaz,
SWAT,
};



UCLASS()
class TACTICALOPS_API ATOPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	
	ATOPlayerState();

	

	UPROPERTY(Replicated)
		uint16 NumKills;

	UPROPERTY(Replicated)
		uint16 NumDeaths;

	UPROPERTY(Replicated)
		uint16 TeamMateKilled;

	UPROPERTY(Replicated)
		ETeamKindEnum TeamNumber;

	//Le nombre de tirs effectués: Ne prends pas en compte les shotguns
	UPROPERTY(Replicated)
		uint16 NumBulletsFired;
	//le nombre de shotgun
	UPROPERTY(Replicated)
		uint16 NumShotFired;
	//le nombre de tirs qui ont touché une cible
	UPROPERTY(Replicated)
		uint16 NumFiredTarget;
	//le nombre de tirs de shotqui ont touché une cible
	UPROPERTY(Replicated)
		uint16 NumShotTarget;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Gestion de la team
	//UFUNCTION(BlueprintPure, Category = PlayerState)
	//	ETeamKindEnum GetTeam() const { return Team; };
	/**
	* Set new team and update pawn. Also updates player character team colors.
	*
	* @param	NewTeamNumber	Team we want to be on.
	*/

	void SetTeam(ETeamKindEnum NewTeam);

	/** get current team */
	//int32 GetTeamNum() const;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	void AddBshotsTarget(int32 NumShots);

	void AddBulletTarget(int32 NumBullets);

	void AddBshotsFired(int32 NumShots);

	void AddBulletsFired(int32 NumBullets);



	/** get number of kills */
	UFUNCTION(BlueprintPure, Category = PlayerState)
		int32 GetKills() const;
	/** get number of deaths */
	UFUNCTION(BlueprintPure, Category = PlayerState)
		int32 GetDeaths() const;

	/** get number of mate's deaths */
	UFUNCTION(BlueprintPure, Category = PlayerState)
		int32 GetTeamKilled() const;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Begin APlayerState interface
	/** clear scores */
	virtual void Reset() override;


	



};