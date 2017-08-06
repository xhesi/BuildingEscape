// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "OpenDoor.h"


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	//GetOwner()->GetTransform().GetRotation().GetAxisY().ToString()
	UE_LOG(LogTemp, Warning, TEXT("Rotation %s"), *(GetOwner()->GetTransform().GetRotation().GetAxisY().ToString()));
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{

	// create rotator
	FRotator NewRotation = FRotator(0.0f, OpenAngle, 0.0f);

	// set the door rotation
	Owner->SetActorRotation(NewRotation);

	
}

void UOpenDoor::CloseDoor()
{
	
	// create rotator
	FRotator NewRotation = FRotator(0.0f, 0.0f, 0.0f);

	// set the door rotation
	Owner->SetActorRotation(NewRotation);


}


// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger volume
	// if the ActorThatOpens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetRealTimeSeconds();
	}
	if (GetWorld()->GetRealTimeSeconds() > LastDoorOpenTime + DoorCloseDelay)
	{
		CloseDoor();
	}
}

