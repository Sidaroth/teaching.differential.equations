// Copyright 2016 Christian Holt

#pragma once

#include "GameFramework/Pawn.h"
#include "Journal.h"

#include "Player_CPP.generated.h"


UCLASS()
class TITANIUM_API APlayer_CPP : public APawn
{
	GENERATED_BODY()
public:
	// Sets default values for this pawn's properties
	APlayer_CPP();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* inputComp) override;

protected:
	UCameraComponent* camera;
	FVector2D MovementInput;
	FVector2D CameraInput;
	UPROPERTY(EditAnywhere)
	UJournal* JournalComponent;

	// Input functions
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void PitchCamera(float AxisValue);
	void YawCamera(float AxisValue);
	void ToggleJournal();
};
