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

	SetFiles();
	SetCommands();
	SetFolderTree();
	SetFilesInFolders();
	currentFolder = Folders["C:/User"];
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

void UTerminalLogic::SetFiles() {
	files[0].name = "File1.txt";
	files[1].name = "File2.txt";
	files[2].name = "File3.txt";
	files[3].name = "File4.txt";
	files[4].name = "File5.txt";
	files[5].name = "File6.txt";

	files[0].content = "Lorem Ipsum1";
	files[1].content = "Lorem Ipsum2";
	files[2].content = "Lorem Ipsum3";
	files[3].content = "Lorem Ipsum4";
	files[4].content = "Lorem Ipsum5";
	files[5].content = "Lorem Ipsum6";
}

void UTerminalLogic::SetFilesInFolders() {
	TArray<TPair<FString,SFolder>> foldersArray  = Folders.Array();
	int foldersCount = foldersArray.Num();
	for (int i = 0; i < 6; i++)
	{
		int randomFolderIndex = rand() % foldersCount;
		Folders[foldersArray[randomFolderIndex].Value.Path].ChildrenFiles.Add(files[i].name);
		Files.Add(foldersArray[randomFolderIndex].Value.Path + "/" + files[i].name, MoveTemp(files[i]));

	}
}

void UTerminalLogic::SetFolders(SFolder &folder, int deep)
{
	if (deep > 4 || foldersPool.Num()-1 == 0)
		return;
	int foldersNumber = 0;
	if (foldersPool.Num()-1 < 3)
		foldersNumber = foldersPool.Num() - 1;
	else
		foldersNumber = (rand() % 3)+1;
	
	for (int i = 0; i < foldersNumber; i++)
	{
		int FolderIndex = (rand() % (foldersPool.Num()-1)) + 1;
		folder.ChildrenFolders.Add(foldersPool[FolderIndex].Name);
		foldersPool[FolderIndex].Path = folder.Path + "/" + foldersPool[FolderIndex].Name;
		foldersPool[FolderIndex].ParentFolderPath = folder.Path;
		Folders.Add(foldersPool[FolderIndex].Path, MoveTemp(foldersPool[FolderIndex]));
		foldersPool.RemoveAt(FolderIndex);
				
	}
	deep += 1;
	for (int i = 0; i < foldersNumber; i++)
	{	if (rand() % 100 > 30)
			SetFolders(Folders[folder.Path + "/" + folder.ChildrenFolders[i]], deep);
	}
		
}

void UTerminalLogic::SetFolderTree()
{
	folders[0].Name = "User";
	folders[0].Path = "C:/User";
	

	folders[1].Name = "Folder1";
	folders[2].Name = "Folder2";
	folders[3].Name = "Folder3";
	folders[4].Name = "Folder4";
	folders[5].Name = "Folder5";
	folders[6].Name = "Folder6";
	folders[7].Name = "Folder7";
	folders[8].Name = "Folder8";
	folders[9].Name = "Folder9";
	folders[10].Name = "Folder10";
	folders[11].Name = "Folder11";
	folders[12].Name = "Folder12";
	folders[13].Name = "Folder13";
	folders[14].Name = "Folder14";
	folders[15].Name = "Folder15";
	folders[16].Name = "Folder16";
	folders[17].Name = "Folder17";
	folders[18].Name = "Folder18";
	folders[19].Name = "Folder19";
	folders[20].Name = "Folder20";
	folders[21].Name = "Folder21";
	folders[22].Name = "Folder22";
	folders[23].Name = "Folder23";
	folders[24].Name = "Folder24";
	folders[25].Name = "Folder25";
	folders[26].Name = "Folder26";
	folders[27].Name = "Folder27";
	folders[28].Name = "Folder28";
	folders[29].Name = "Folder29";
	for (auto& Elem : folders)
		foldersPool.Add(Elem);
	SetFolders(folders[0], 0);
	Folders.Add(folders[0].Path, MoveTemp(folders[0]));

	
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

	commands[5].commandName = "cat";
	commands[5].function = &UTerminalLogic::Cat;
	commands[5].description.Add(TEXT("Print files content"));
	commands[5].description.Add(TEXT("Specific file you want to print"));
	commands[5].parameters.Add(TEXT("[file name]"));
	commands[5].parametersCount = 1;
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
	FString output = currentFolder.Path + "/\n";

	for (auto& Elem : currentFolder.ChildrenFolders) {
		output += "\t*" + Elem + "\n";
	}
	for (auto& Elem : currentFolder.ChildrenFiles) {
		output += "\t-" + Elem + "\n";
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
FString UTerminalLogic::Cat(FString arguments) {
	if (arguments == "NONE")
		return "No file was parsed as an parameter";
	else if(Files.Contains(arguments))
		return Files[arguments].content;
	else if(Files.Contains(currentFolder.Path + "/" + arguments))
		return Files[currentFolder.Path + "/" + arguments].content;
	else
		return "No such file was found";
}
