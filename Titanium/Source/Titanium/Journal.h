// Copyright 2016 Christian Holt

#pragma once

#include "Components/ActorComponent.h"
#include "Journal.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TITANIUM_API UJournal : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJournal();

	// Called when the game starts
	virtual void BeginPlay() override;

	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	
	UFUNCTION(BlueprintCallable, Category="Journal")
	void Toggle();

protected:
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BookVisual;
	UPROPERTY(EditAnywhere)
	UMaterial* BookMaterial;
	bool isToggled;
	FVector distanceFromFace;
	FVector tilt;

	void UpdateWorldPosition();
};
