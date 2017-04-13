// Fill out your copyright notice in the Description page of Project Settings.

#include "TacticalOps.h"
#include "BaseGameInstance.h"


UBaseGameInstance::UBaseGameInstance()
{
	LevelLibrary = UObjectLibrary::CreateLibrary(UWorld::StaticClass(), false, GIsEditor);
	LevelLibrary->AddToRoot();
	LevelLibrary->LoadAssetDataFromPath(TEXT("/Game/Maps"));
	

}


void UBaseGameInstance::GetLevels(TArray<FName> & OutLevels)
{
	TArray<FAssetData> AssetDatas;
	LevelLibrary->GetAssetDataList(AssetDatas);

	for (int32 i = 0; i < AssetDatas.Num(); ++i)
	{
		FAssetData & AssetData = AssetDatas[i];
		OutLevels.Add(AssetData.AssetName);
	}

	//GetAssetsFromLibrary<UWorld>(LevelLibrary, OutLevels);
}