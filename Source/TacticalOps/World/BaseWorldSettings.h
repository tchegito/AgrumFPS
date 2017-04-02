// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/WorldSettings.h"
#include "BaseWorldSettings.generated.h"

/**
 * 
 */

 // Struct to store information about teams
USTRUCT()
struct FTeamStruct2
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
class TACTICALOPS_API ABaseWorldSettings : public AWorldSettings
{
	GENERATED_BODY()
	
public:
	// Camera being used as a view target in spawn screen etc.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WorldSettings)
		TArray<ACameraActor *> MenuCameras;

		// Mesh to use for players in team A or all players in FFA
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WorldSettings)
		TArray<USkeletalMesh *> TeamASoldierMeshes;
	
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = WorldSettings)
			TArray<FTeamStruct2> KindTeam;
};
