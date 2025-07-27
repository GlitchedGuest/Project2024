// Fill out your copyright notice in the Description page of Project Settings.


#include "TerminalLogic.h"

// Sets default values for this component's properties
UTerminalLogic::UTerminalLogic()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTerminalLogic::BeginPlay()
{
	Super::BeginPlay();

	SetCommands();
}


// Called every frame
void UTerminalLogic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UTerminalLogic::ExecuteCommand(FString command)
{
	
	for (int i = 0; i < commandsCount; i++) {
		if (command == commands[i].commandName)
			return (this->*commands[i].function)();
	}
	return "No such command as " + command;
}

FString UTerminalLogic::Help()
{
	FString output = "";
	for (int i = 0; i < commandsCount; i++)
		output += "\n" + commands[i].commandName + " - " + commands[i].description ;
	return output;
}

void UTerminalLogic::SetCommands()
{
	commands[0].commandName = "Help";
	commands[0].function = &UTerminalLogic::Help;
	commands[0].description = "See list of the commands and what they do";

	commands[1].commandName = "Camera";
	commands[1].function = &UTerminalLogic::Camera;
	commands[1].description = "Open camera system";
}

FString UTerminalLogic::Camera()
{
	return "Opening camera system";
}