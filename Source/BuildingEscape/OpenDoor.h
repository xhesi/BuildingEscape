// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "OpenDoor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDoorRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

	// Called when the game starts
	virtual void BeginPlay() override;

	
	// Called every frame	
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(BlueprintAssignable)
	FDoorRequest OnOpenRequest;

	UPROPERTY(BlueprintAssignable)
	FDoorRequest OnCloseRequest;

private:

	UPROPERTY(EditAnywhere)
	ATriggerVolume* PressurePlate;
	

	AActor* Owner = GetOwner();

	float GetTotalMassOfActorsOnPlate();

	UPROPERTY(EditAnywhere)
	float WeightThreshold = 10.f;


};
