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
	if (GEngine)
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("TEST2"));

	helpCommand.commandName = "Help";
	helpCommand.function = &UTerminalLogic::Help;
	helpCommand.Description = "Work in Progress";
	
}


// Called every frame
void UTerminalLogic::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FString UTerminalLogic::ExecuteCommand(FString command)
{
	return (this->*helpCommand.function)();
}

FString UTerminalLogic::Help()
{
	return "Tu beda opisane instrukcje";
}