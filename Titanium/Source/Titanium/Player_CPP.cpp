// Copyright 2016 Christian Holt

#include "Titanium.h"
#include "Player_CPP.h"

// Sets default values
APlayer_CPP::APlayer_CPP()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Make components
	USphereComponent* SphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = SphereComponent;
	SphereComponent->InitSphereRadius(40.f);
	SphereComponent->SetCollisionProfileName(TEXT("Pawn"));

	UStaticMeshComponent* SphereVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("VisualRepresentation"));
	SphereVisual->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereVisualAsset(TEXT("/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere"));

	if (SphereVisualAsset.Succeeded()) {
		SphereVisual->SetStaticMesh(SphereVisualAsset.Object);
		SphereVisual->SetRelativeLocation(FVector(0.0f, 0.0f, -40.f));
		SphereVisual->SetWorldScale3D(FVector(0.8f));
	}

	camera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	camera->SetupAttachment(RootComponent);

	JournalComponent = CreateDefaultSubobject<UJournal>(TEXT("JournalComponent"));

	// Take control of the default player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void APlayer_CPP::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APlayer_CPP::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);

	NewRotation = camera->GetComponentRotation();
	NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CameraInput.Y, -75.f, 75.f);

	if (!MovementInput.IsZero()) {
		MovementInput = MovementInput.GetSafeNormal() * 100.0f;
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * MovementInput.X * DeltaTime;
		NewLocation += GetActorRightVector() * MovementInput.Y * DeltaTime;
		SetActorLocation(NewLocation);
	}
}

// Called to bind functionality to input
void APlayer_CPP::SetupPlayerInputComponent(class UInputComponent* inputComp)
{
	Super::SetupPlayerInputComponent(inputComp);

	inputComp->BindAction("ToggleJournal", IE_Pressed, this, &APlayer_CPP::ToggleJournal);
	inputComp->BindAxis("MoveForward", this, &APlayer_CPP::MoveForward);
	inputComp->BindAxis("MoveRight", this, &APlayer_CPP::MoveRight);
	inputComp->BindAxis("CameraYaw", this, &APlayer_CPP::YawCamera);
	inputComp->BindAxis("CameraPitch", this, &APlayer_CPP::PitchCamera);
}

void APlayer_CPP::YawCamera(float AxisValue)
{
	CameraInput.X = AxisValue;
}

void APlayer_CPP::PitchCamera(float AxisValue)
{
	CameraInput.Y = AxisValue;
}

void APlayer_CPP::MoveForward(float AxisValue)
{
	MovementInput.X = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APlayer_CPP::MoveRight(float AxisValue)
{
	MovementInput.Y = FMath::Clamp<float>(AxisValue, -1.0f, 1.0f);
}

void APlayer_CPP::ToggleJournal()
{
	
}
