// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow,FString::Printf(TEXT("TALTAL")));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//get player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewLocation, OUT ViewRotation);
	//cast a ray
	LineTraceEnd = ViewLocation + (ViewRotation.Vector() * Reach);
	DrawDebugLine(GetWorld(), ViewLocation,LineTraceEnd , FColor::Red, false, 0, 0.f, 7.f);
	//print it.

	//whenever you use print always use * before the variable so that it will work.
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("%s , %s"), *ViewLocation.ToString(),*ViewRotation.ToString()));

	
}

