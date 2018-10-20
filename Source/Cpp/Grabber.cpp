// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT


// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	Initialize();
	CheckInputComponent();
	
}



// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UpdateLineTrace();
	
}

void UGrabber::GrabNow()
{
	auto HitResult =  HitLineTrace();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();

	if (ActorHit)
	{
		HandleComponent->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
	}

	
}

void UGrabber::ReleaseNow()
{
	HandleComponent->ReleaseComponent();
}

FHitResult UGrabber::HitLineTrace()
{
	
	FHitResult Hit = EndLineTrace();

	//print it.
	AActor* ActorHit = Hit.GetActor();
	if (ActorHit)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("%s"), *(ActorHit->GetName())));
	}

	return Hit;
}

void UGrabber::Initialize()
{
	HandleComponent = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
}

void UGrabber::CheckInputComponent()
{
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::GrabNow);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::ReleaseNow);
	}
}
	
FHitResult  UGrabber::EndLineTrace()
{
	//get player view point
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT ViewLocation, OUT ViewRotation);
	//cast a ray
	LineTraceEnd = ViewLocation + (ViewRotation.Vector() * Reach);

	//Create query parameter
	FCollisionQueryParams CollisionQuery = (FName(TEXT("")), false, GetOwner());

	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(OUT Hit, ViewLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), CollisionQuery);
	return Hit;
}

void UGrabber::UpdateLineTrace()
{
	EndLineTrace();

	if (HandleComponent->GrabbedComponent)
	{
		HandleComponent->SetTargetLocation(LineTraceEnd);
	}
}
//whenever you use print always use * before the variable so that it will work.
	//GEngine->AddOnScreenDebugMessage(-1, 2, FColor::Yellow, FString::Printf(TEXT("%s , %s"), *ViewLocation.ToString(),*ViewRotation.ToString()));

	//draw debug line
	//DrawDebugLine(GetWorld(), ViewLocation, LineTraceEnd, FColor::Red, false, 0, 0.f, 7.f);




