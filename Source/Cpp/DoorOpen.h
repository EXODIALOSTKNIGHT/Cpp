// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "Engine/GameEngine.h"
#include "Engine/Classes/Components/PrimitiveComponent.h"
#include "DoorOpen.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPP_API UDoorOpen : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpen();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoorNow();
	void CloseDoorNow();
	float GetActorTotalMass();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	AActor* Owner = GetOwner();

	UPROPERTY(EditAnywhere)
		FRotator OpenAngle = FRotator(0, 0, 0);
	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate = nullptr;
	UPROPERTY(EditAnywhere)
		float DelayTime = 0;
	float CurrentTime;

	UPROPERTY(EditAnywhere)
		float OpenDoorThreshold = 60.f;

	
	

	

	
	
	
	
};
