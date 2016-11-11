// Copyright 2016 Christian Holt

#pragma once

#include "Components/ActorComponent.h"
#include "Temperature.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TITANIUM_API UTemperature : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTemperature();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere, meta = (DisplayName = "Body Temperature (C)", ClampMin = "20.0", ClampMax = "45.0", UIMin = "20.0", UIMax = "45.0"))
		float BodyTemperature = 37.0f;

	void SetBodyTemperature(float);
	float GetBodyTemperature();
};
