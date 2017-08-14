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
	
}



// Called every frame
void UOpenDoor::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Poll the trigger volume
	// if the weigh in the volume is greate than threshhold

	 if (GetTotalMassOfActorsOnPlate() > WeightThreshold)
	//if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		 OnOpenRequest.Broadcast();
	} else {
		 OnCloseRequest.Broadcast();
	}
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;
	TArray<AActor*> OverlappingActors;
	// Find all overlapping actors
	PressurePlate->GetOverlappingActors(OverlappingActors);
	UE_LOG(LogTemp, Warning, TEXT("----"));
	for (AActor* CurrentActor : OverlappingActors) {
		TotalMass += CurrentActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		UE_LOG(LogTemp, Warning, TEXT("Mass: %s"), *(CurrentActor->GetName()));
		
	}
	// iterate over them 
	
	return TotalMass;
}

