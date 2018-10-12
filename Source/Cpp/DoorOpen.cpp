// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"


// Sets default values for this component's properties
UDoorOpen::UDoorOpen()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpen::BeginPlay()
{
	Super::BeginPlay();

	ActorThatOpen = GetWorld()->GetFirstPlayerController()->GetPawn();
	
}

void UDoorOpen::OpenDoorNow()
{

	Owner->SetActorRotation(OpenAngle);
}

void UDoorOpen::CloseDoorNow()
{

	Owner->SetActorRotation(FRotator(0,0,0));
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// add PressurePlate&&PressurePlate to avoid crashing the editor when playing
	if (PressurePlate&&PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoorNow();
		CurrentTime = GetWorld()->GetTimeSeconds();
		//print string in UE4
		//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("%f"), CurrentTime));
	}

	if (GetWorld()->GetTimeSeconds() - CurrentTime > DelayTime)

	{
			CloseDoorNow();
	}

	
	
}



