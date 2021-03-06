// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/GameEngine.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"
#include "DrawDebugHelpers.h"
#include "Engine/EngineTypes.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	

private:
	FVector ViewLocation;
	FRotator ViewRotation;

	FVector LineTraceEnd;
	float Reach = 80.f;
	UPhysicsHandleComponent* HandleComponent = nullptr;
	UInputComponent* InputComponent = nullptr;

	void GrabNow();
	void ReleaseNow();
	void UpdateLineTrace();
	FHitResult HitLineTrace();
	FHitResult EndLineTrace();
	
	void Initialize();
	void CheckInputComponent();
	
};
