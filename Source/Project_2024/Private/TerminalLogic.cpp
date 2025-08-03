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

	folders[0].Name = "Folder1";
	folders[1].Name = "Folder2";

	startingFolder.Name = "User";
	startingFolder.Folders.Add("Folder1", MakeUnique<SFolder>(MoveTemp(folders[0])));
	startingFolder.Folders.Add("Folder2", MakeUnique<SFolder>(MoveTemp(folders[1])));

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

	commands[2].commandName = "Status";
	commands[2].function = &UTerminalLogic::Status;
	commands[2].description = "Display subject's status";

	commands[3].commandName = "ls";
	commands[3].function = &UTerminalLogic::List;
	commands[3].description = "Display contents of the current folder";
}

FString UTerminalLogic::Camera()
{
	return "Opening camera system";
}

FString UTerminalLogic::Status()
{
	return "Subject's Status:";
}

FString UTerminalLogic::List()
{
	FString output = "C:/" + startingFolder.Name + "/\n";

	for (auto& Elem : startingFolder.Folders) {
		output += Elem.Value->Name + "\n";
	}

	return output;
}