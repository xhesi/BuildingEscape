// Fill out your copyright notice in the Description page of Project Settings.

#include "BuildingEscape.h"
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
	
	FindPhysicsHandleComponent();
	SetupInputComponent();
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key pressed!"));

	/// Try and reach any actors with physics body collision channel set
	FHitResult Hit = GetFirstPhysicsBodyInReach();
	// see what we hit
	AActor* ActorHit = Hit.GetActor();
	/// If we hit somethign then attach a physics handle
	if (ActorHit)
	{
		InitialRotation = GetPlayerRotation()- Hit.GetComponent()->GetOwner()->GetActorRotation();
		UE_LOG(LogTemp, Warning, TEXT("Linetrace hit: %s"), *(ActorHit->GetName()));
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			Hit.GetComponent(),
			NAME_None,
			Hit.GetComponent()->GetOwner()->GetActorLocation(),
			Hit.GetComponent()->GetOwner()->GetActorRotation()
		);


	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key released!"));

	// TODO release physics handle
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandleComponent()
{
	/// look for attached physics handle
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle for %s does not exist!"), *(GetOwner()->GetName()));
	}
}

void UGrabber::SetupInputComponent()
{
	/// look for attached input component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent on %s found!"), *(GetOwner()->GetName()));
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent for %s does not exist!"), *(GetOwner()->GetName()));
	}
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	
	
	/// Ray cast out to reach distance
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		GetReachLineBegin(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return Hit;
}

FVector UGrabber::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	// Get player view point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
	return LineTraceEnd;
}

FRotator UGrabber::GetPlayerRotation()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	// Get player view point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointRotation;
}

FVector UGrabber::GetReachLineBegin()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	// Get player view point this tick
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// If the physics handle is attached
	if (PhysicsHandle->GrabbedComponent)
	{		
		FRotator NewRotation = GetPlayerRotation() - InitialRotation;
		NewRotation.Pitch = 0.f;
		NewRotation.Roll = 0.f;
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
		PhysicsHandle->SetTargetRotation(NewRotation);
	}
	
	
}

