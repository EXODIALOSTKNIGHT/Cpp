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

	HandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabNow);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseNow);
	}
}

void UGrabber::GrabNow()
{
	GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("Grab")));
}

void UGrabber::ReleaseNow()
{
	GEngine->AddOnScreenDebugMessage(-3, 2, FColor::Red, FString::Printf((TEXT("Release"))));
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

	//detect object

	//Create query parameter
	FCollisionQueryParams CollisionQuery = (FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit,ViewLocation,LineTraceEnd,FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),CollisionQuery);
	
	//print it.
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("%s"), *(ActorHit->GetName())));
	}




	//whenever you use print always use * before the variable so that it will work.
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("%s , %s"), *ViewLocation.ToString(),*ViewRotation.ToString()));

	
}



