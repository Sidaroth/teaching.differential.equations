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
		InputComponent->BindAction("Interact", IE_Pressed, this, &UBodyInteract::Interact);
	} else {
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName());
	}
}

void UBodyInteract::Measure(AActor* ActorHit)
{
	auto TemperatureComponent = (UTemperature*) ActorHit->GetComponentByClass(UTemperature::StaticClass());
	if (TemperatureComponent) {
		FString details = "Body height: 175cm.\nBody weight: 72kg.\nBody Temperature: ";
		details.Append(FString::SanitizeFloat(TemperatureComponent->GetBodyTemperature()));
		details.Append(" celsius.\n");

		HUD->SetTemperatureString(details);
		HUD->SetTemperatureVisibility(true);
	}
}

void UBodyInteract::Exit()
{
	FString currentLevel = GetWorld()->GetMapName();
	if (DEBUG) UE_LOG(LogTemp, Warning, TEXT("Level: %s"), *currentLevel);

	UGameplayStatics::OpenLevel(GetWorld(), "SuspectLineup", false);
}

// Interact
void UBodyInteract::Interact()
{
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ActorHit = HitResult.GetActor();
	
	if (ActorHit) {
		if(DEBUG) UE_LOG(LogTemp, Warning, TEXT("Actor hit: %s"), *ActorHit->GetName())
		if (ActorHit->GetName() == "DeadBody1") {
			Measure(ActorHit);
		}
		else if (ActorHit->GetName() == "ExitDoor1") {
			Exit();
		}
	}
}

/// Line-trace (Ray-cast) out to reach distance and return first physics body in reach, if any. 
const FHitResult UBodyInteract::GetFirstPhysicsBodyInReach()
{
	if (DEBUG) {
		DrawDebugLine(
			GetWorld(),
			GetReachLineStart(),
			GetReachLineEnd(),
			FColor(255, 0, 0),
			false, 1, 0,
			12.333
		);
	}
	
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
		VisibleFor = 4.0f;
		HUD->SetTemperatureVisibility(false);
	}
}
