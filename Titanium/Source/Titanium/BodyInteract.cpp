// Copyright 2016 Christian Holt

#include "Titanium.h"
#include "BodyInteract.h"
#include "Temperature.h"


// Sets default values for this component's properties
UBodyInteract::UBodyInteract()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UBodyInteract::BeginPlay()
{
	Super::BeginPlay();

	HUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	SetupInputComponent();
}

void UBodyInteract::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent) {
		InputComponent->BindAction("Measure", IE_Pressed, this, &UBodyInteract::Measure);
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
	}
}

void UBodyInteract::Measure()
{
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	auto ActorHit = HitResult.GetActor();
	
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Measure: %s"), *ActorHit->GetName());
		
		auto TemperatureComponent = (UTemperature*) ActorHit->GetComponentByClass(UTemperature::StaticClass());
		if (TemperatureComponent) {
			FString temperature = "Temperature is: ";
			temperature.Append(FString::SanitizeFloat(TemperatureComponent->GetBodyTemperature()));
			temperature.Append(" celsius.");

			HUD->SetTemperatureString(temperature);
			HUD->SetTemperatureVisibility(true);
		}
	}
}

/// Line-trace (Ray-cast) out to reach distance and return first physics body in reach, if any. 
const FHitResult UBodyInteract::GetFirstPhysicsBodyInReach()
{
	DrawDebugLine(
		GetWorld(),
		GetReachLineStart(),
		GetReachLineEnd(),
		FColor(255, 0, 0),
		false, 1, 0,
		12.333
	);

	FHitResult HitResult;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	return HitResult;
}

FVector UBodyInteract::GetReachLineStart()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation;
}

FVector UBodyInteract::GetReachLineEnd()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

// Called every frame
void UBodyInteract::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// Move to HUD
	VisibleFor -= DeltaTime;
	if (VisibleFor < 0) {
		VisibleFor = 2.0f;
		HUD->SetTemperatureVisibility(false);
	}
}
