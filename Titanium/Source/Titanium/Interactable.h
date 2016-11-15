// Copyright 2016 Christian Holt

#pragma once

#include "Interactable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};


class TITANIUM_API IInteractable
{
	GENERATED_IINTERFACE_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void OnInteract(AController* user);
	virtual void DisplayPrompt(UCanvas* canvas, AController* user);
};
