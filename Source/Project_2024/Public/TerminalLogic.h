// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TerminalLogic.generated.h"

struct SCommand {
public:
	FString commandName;
	FString (UTerminalLogic::*function)();
	FString description;
};

struct SFile {
	FString name;
};

struct SFolder {
	FString Name;
	TArray<SFile> Files;
	TMap<FString, TUniquePtr<SFolder>> Folders;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable )
class PROJECT_2024_API UTerminalLogic : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTerminalLogic();
	SFolder startingFolder;
	SFolder folders[2];

	SCommand commands[4];
private:
	int commandsCount = 4;

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
	FString Help();
	FString Camera();
	FString Status();
	FString List();
};
