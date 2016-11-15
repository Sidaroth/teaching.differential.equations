// Copyright 2016 Christian Holt

#include "Titanium.h"
#include "Interactable.h"


// This function does not need to be modified.
UInteractable::UInteractable(const class FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{
}

// Add default functionality here for any IInteractable functions that are not pure virtual.

void IInteractable::OnInteract(AController* user)
{

}

void IInteractable::DisplayPrompt(UCanvas* canvas, AController* user)
{

}