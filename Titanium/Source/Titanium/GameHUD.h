// Copyright 2016 Christian Holt

#pragma once

#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class TITANIUM_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	AGameHUD();

public:
	UPROPERTY()
	UFont* HUDFont;

	virtual void DrawHUD() override;
	FString TemperatureString;
	bool TemperatureVisible; 

	void SetTemperatureString(FString);
	void SetTemperatureVisibility(bool);
};
