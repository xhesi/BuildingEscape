// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
#include "PositionReport.h"
#include "Gameframework/actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	FString ObjectName = GetOwner()->GetName();
	FString ObjectPos = "X= something, Y=something else, etc";
	ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();
	UE_LOG(LogTemp, Warning, TEXT("%s ist at %s"), *ObjectName, *ObjectPos);

	//UE_LOG(LogTemp, Warning, TEXT("Position report reporting for duty on "));
	
}


// Called every frame
void UPositionReport::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

