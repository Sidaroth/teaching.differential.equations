// Copyright 2016 Christian Holt

#include "Titanium.h"
#include "Journal.h"


// Sets default values for this component's properties
UJournal::UJournal()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;

	USceneComponent* RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Journal"));
	BookVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Visual"));
	BookVisual->SetupAttachment(RootComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> BookVisualAsset (TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("Material'/Game/Journal/JournalTextureTexted_Mat.JournalTextureTexted_Mat'"));

	if (BookVisualAsset.Succeeded()) {
		BookVisual->SetStaticMesh(BookVisualAsset.Object);
		BookVisual->SetRelativeLocation(FVector(100.0f, 100.0f, 100.0f));
	}

	if (MaterialAsset.Succeeded()) {
		BookMaterial = MaterialAsset.Object;
	}
}

// Called when the game starts
void UJournal::BeginPlay()
{
	Super::BeginPlay();

	BookVisual->SetMaterial(0, BookMaterial);
	BookVisual->SetWorldScale3D(FVector(0.02f, 0.15f, 0.15f));
	isToggled = false;
}

void UJournal::UpdateWorldPosition()
{
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	FVector NewLocation = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * 13.0f;
	NewLocation += FVector(0.0f, 0.0f, -9.f);

	BookVisual->SetRelativeLocation(NewLocation);
	BookVisual->SetWorldRotation(PlayerViewPointRotation);
}

// Called every frame
void UJournal::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
	UpdateWorldPosition();

	BookVisual->SetVisibility(isToggled);
}

void UJournal::Toggle()
{
	isToggled = !isToggled;
	UE_LOG(LogTemp, Warning, TEXT("Journal toggle: %s"), isToggled ? TEXT("true") : TEXT("false"));
}

