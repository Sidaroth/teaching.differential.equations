// Copyright 2016 Christian Holt

#pragma once

#include "Components/ActorComponent.h"
#include "GameHUD.h"
#include "BodyInteract.generated.h"

#define OUT 

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TITANIUM_API UBodyInteract : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBodyInteract();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere)
		bool DEBUG = true;
		
protected:
	float Reach = 200.f;

	UInputComponent* InputComponent = nullptr;
	AGameHUD* HUD = nullptr;

	void SetupInputComponent();
	void Interact();
	void Measure(AActor*);
	void Exit();

	float VisibleFor = 2.0f;

	// Return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();
	// Returns current start of reach line
	FVector GetReachLineStart();
	// Returns current end of reach line
	FVector GetReachLineEnd();
};
