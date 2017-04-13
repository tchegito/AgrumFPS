// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "BaseGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TACTICALOPS_API UBaseGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
		// Asset library for all levels
		UObjectLibrary * LevelLibrary;
	
	UBaseGameInstance();

	UFUNCTION(BlueprintCallable, Category = Library)
		void GetLevels(TArray<FName> & OutLevels);

private:
	template<typename T>
	void GetAssetsFromLibrary(UObjectLibrary * Library, TArray<T *> & OutAssets);

	template<typename T>
	TSubclassOf<T> GetBlueprintClassFromLibrary(UObjectLibrary * Library, const FName & ClassName);

	template<typename T>
	void GetBlueprintClassesFromLibrary(UObjectLibrary * Library, TArray<TSubclassOf<T>> & OutClasses);


};



template<typename T>
inline TSubclassOf<T> UBaseGameInstance::GetBlueprintClassFromLibrary(UObjectLibrary * Library, const FName & ClassName)
{
	TArray<UBlueprintGeneratedClass *> ClassesArray;
	Library->GetObjects<UBlueprintGeneratedClass>(ClassesArray);

	for (int32 i = 0; i < ClassesArray.Num(); ++i)
	{
		UClass * BlueprintClass = ClassesArray[i];
		if (BlueprintClass->GetFName() == ClassName)
		{
			return BlueprintClass;
		}
	}

	return NULL;
}


template<typename T>
inline void UBaseGameInstance::GetBlueprintClassesFromLibrary(UObjectLibrary * Library, TArray<TSubclassOf<T>> & OutClasses)
{
	OutClasses.Empty();

	TArray<UBlueprintGeneratedClass *> ClassesArray;
	Library->GetObjects<UBlueprintGeneratedClass>(ClassesArray);

	for (int32 i = 0; i < ClassesArray.Num(); ++i)
	{
		UBlueprintGeneratedClass * BlueprintClass = ClassesArray[i];
		if (!BlueprintClass->GetName().StartsWith("SKEL_"))
		{
			OutClasses.Add(BlueprintClass);
		}
	}

}