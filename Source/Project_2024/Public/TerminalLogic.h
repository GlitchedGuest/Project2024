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
};

struct SFolder {
	FString Name;
	FString Path;
	FString ParentFolderPath;
	TArray<FString> ChildrenFolders;
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

	SCommand commands[5];
private:
	int commandsCount = 5;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintCallable, Category = "Terminal")
	FString ExecuteCommand(FString command);

private:
	void SetCommands();
	void SetFolderTree();
	FString Help(FString arguments);
	FString Camera(FString arguments);
	FString Status(FString arguments);
	FString List(FString arguments);
	FString SwitchDirectory(FString arguments);
};
