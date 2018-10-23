// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpen.h"

#define OUT

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

	OnOpenRequest.Broadcast();
}

void UDoorOpen::CloseDoorNow()
{
	OnCloseRequest.Broadcast();
}




// Called every frame
void UDoorOpen::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	// add PressurePlate&&PressurePlate to avoid crashing the editor when playing
	if (GetActorTotalMass() > OpenDoorThreshold)
	{
		OpenDoorNow();
	}
	else
	{
		CloseDoorNow();
	}
	
}

float UDoorOpen::GetActorTotalMass()
{
	float TotalMass = 0.f;

	if (!PressurePlate){ return TotalMass = 0; }
	
	
	TArray<AActor*> OverlappingActor;
	PressurePlate->GetOverlappingActors(OUT OverlappingActor);

	for (auto& ActorOverlap : OverlappingActor)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("%s"), *ActorOverlap->GetName()));
		TotalMass += ActorOverlap->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}

	return TotalMass;
}



