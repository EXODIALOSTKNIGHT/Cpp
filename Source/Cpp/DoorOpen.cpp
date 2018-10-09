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

	
}

void UDoorOpen::OpenDoorNow()
{
	FRotator CurrentAngle = Owner->GetActorRotation();
	FRotator DoorOpenAngle = CurrentAngle + OpenAngle;
	Owner->SetActorRotation(DoorOpenAngle);
}


// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// add PressurePlate&&PressurePlate to avoid crashing the editor when playing
	if (PressurePlate&&PressurePlate->IsOverlappingActor(ActorThatOpen))
	{
		OpenDoorNow();
	}
}

