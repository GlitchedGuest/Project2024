// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TerminalLogic.generated.h"

struct SCommand {
public:
	FString commandName;
	FString (UTerminalLogic::*function)(FString parameters);
	TArray<FString> description;
	TArray<FString> parameters;
	int parametersCount;
};

struct SFile {
	FString name;
	FString content;
	FString path;
};

struct SFolder {
	FString Name;
	FString Path;
	FString ParentFolderPath;
	TArray<FString> ChildrenFolders;
	TArray<FString> ChildrenFiles;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROJECT_2024_API UTerminalLogic : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTerminalLogic();
	SFolder currentFolder;
	TMap<FString, SFolder> Folders;
	SFolder folders[4];
	SFile files[2];
	TMap<FString, SFile> Files;

	SCommand commands[6];
private:
	int commandsCount = 6;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Terminal")
	FString ExecuteCommand(FString command);

private:
	void SetFiles();
	void SetCommands();
	void SetFolderTree();
	FString Help(FString arguments);
	FString Camera(FString arguments);
	FString Status(FString arguments);
	FString List(FString arguments);
	FString SwitchDirectory(FString arguments);
	FString Cat(FString arguments);
};
