// Copyright 2016 Christian Holt

#include "Titanium.h"
#include "Temperature.h"


// Sets default values for this component's properties
UTemperature::UTemperature()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTemperature::BeginPlay()
{
	Super::BeginPlay();

}

void UTemperature::SetBodyTemperature(float temp)
{
	BodyTemperature = temp;
}

float UTemperature::GetBodyTemperature()
{
	UE_LOG(LogTemp, Warning, TEXT("Getting temperature: %f"), BodyTemperature);
	return BodyTemperature;
}


// Called every frame
void UTemperature::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );

	// ...
}

