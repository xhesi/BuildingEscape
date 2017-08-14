// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

private:
	UPhysicsHandleComponent* PhysicsHandle = nullptr;
	UInputComponent* InputComponent = nullptr;
	// grabbing reach
	UPROPERTY(EditAnywhere)
	float Reach = 150.f;

	// ray-cast and grab what's in reach
	void Grab();

	// Called when grab is released
	void Release();

	// Find (assumed) attached physics handle
	void FindPhysicsHandleComponent();

	// Setup (assumed) attached input component
	void SetupInputComponent();
	
	// When gabbing, get the first object in reache via ray casting
	FHitResult GetFirstPhysicsBodyInReach();

	FRotator InitialRotation;

	FVector GetReachLineEnd();
	FVector GetReachLineBegin();
	FRotator GetPlayerRotation();
};
