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
	SetFolderTree();
}


// Called every frame
void UTerminalLogic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UTerminalLogic::ExecuteCommand(FString command)
{
	FString arguments = "NONE";
	FString commandName = command;
	if (command.Find(" ") != -1) {
		arguments = command.Right(command.Len() - command.Find(" ") - 1);
		commandName = command.Left(command.Find(" "));
	}
	for (int i = 0; i < commandsCount; i++) {
		if (commandName == commands[i].commandName)
			return (this->*commands[i].function)(arguments);
	}
	return "No such command as " + command;
}

FString UTerminalLogic::Help(FString arguments)
{
	FString output = "";
	if (arguments == "NONE")		
		for (int i = 0; i < commandsCount; i++) {
			output += commands[i].commandName + " - " + commands[i].description[0];
			if (i != commandsCount - 1)
				output += "\n";
		}		
	else
	{
		for (int i = 0; i < commandsCount; i++)
			if (commands[i].commandName == arguments) {
				output += commands[i].commandName + " - " + commands[i].description[0];
				for (int j = 0; j < commands[i].parametersCount; j++)
				{
					output += "\n" + commands[i].parameters[j] + " - " + commands[i].description[j + 1];
				}
				break;
			}		
	}
	return output;
}

void UTerminalLogic::SetFolderTree()
{
	folders[0].Name = "User";
	folders[0].Path = "C:/User";
	folders[0].ParentFolderPath = "None";
	folders[0].ChildrenFolders.Add("Folder1");
	folders[0].ChildrenFolders.Add("Folder2");

	folders[1].Name = "Folder1";
	folders[1].ParentFolderPath = "C:/User";
	folders[1].Path = "C:/User/Folder1";

	folders[2].Name = "Folder2";
	folders[2].ParentFolderPath = "C:/User";
	folders[2].Path = "C:/User/Folder2";
	folders[2].ChildrenFolders.Add("Folder3");

	folders[3].Name = "Folder3";
	folders[3].Path = "C:/User/Folder1/Folder3";
	folders[3].ParentFolderPath = "C:/User/Folder2";
	
	Folders.Add("C:/User", MoveTemp(folders[0]));
	Folders.Add("C:/User/Folder1", MoveTemp(folders[1]));
	Folders.Add("C:/User/Folder2", MoveTemp(folders[2]));
	Folders.Add("C:/User/Folder2/Folder3", MoveTemp(folders[3]));


	currentFolder = Folders["C:/User"];
}

void UTerminalLogic::SetCommands()
{
	commands[0].commandName = "Help";
	commands[0].function = &UTerminalLogic::Help;
	commands[0].description.Add(TEXT("See list of the commands and what they do"));
	commands[0].description.Add(TEXT("See Specific help for command"));
	commands[0].parameters.Add(TEXT("[command name]"));
	commands[0].parametersCount = 1;

	commands[1].commandName = "Camera";
	commands[1].function = &UTerminalLogic::Camera;
	commands[1].description.Add(TEXT("Open camera system"));
	commands[1].parametersCount = 0;

	commands[2].commandName = "Status";
	commands[2].function = &UTerminalLogic::Status;
	commands[2].description.Add(TEXT("Display subject's status"));
	commands[2].parametersCount = 0;

	commands[3].commandName = "ls";
	commands[3].function = &UTerminalLogic::List;
	commands[3].description.Add(TEXT("Display contents of the current folder"));
	commands[3].parametersCount = 0;

	commands[4].commandName = "cd";
	commands[4].function = &UTerminalLogic::SwitchDirectory;
	commands[4].description.Add(TEXT("Go to directory"));
	commands[4].description.Add(TEXT("Specific folder you want to go"));
	commands[4].parameters.Add(TEXT("[folder name]"));
	commands[4].parametersCount = 1;
}

FString UTerminalLogic::Camera(FString arguments)
{
	return "Opening camera system";
}

FString UTerminalLogic::Status(FString arguments)
{
	return "Subject's Status:";
}

FString UTerminalLogic::List(FString arguments)
{
	FString output = "C:/" + currentFolder.Name + "/\n";

	for (auto& Elem : currentFolder.ChildrenFolders) {
		output += Elem + "\n";
	}

	return output;
}
FString UTerminalLogic::SwitchDirectory(FString arguments)
{
	if (arguments == "NONE")
		currentFolder = Folders["C:/User"];
	else if (arguments == ".." && currentFolder.ParentFolderPath != "None")
		currentFolder = Folders[currentFolder.ParentFolderPath];
	else if (currentFolder.ChildrenFolders.Contains(arguments) == false)
		return "There is no directory: " + arguments;
	else
		currentFolder = Folders[currentFolder.Path + "/" + arguments];
	return "current folder: " +currentFolder.Name;
}
