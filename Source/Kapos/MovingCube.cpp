#include "MovingCube.h"
#include "Camera/CameraComponent.h"

AMovingCube::AMovingCube()
{
	PrimaryActorTick.bCanEverTick = true;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	if (RootMesh)
	{
		SetRootComponent(RootMesh);
	}

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	if (Camera)
	{
		Camera->SetupAttachment(RootMesh);
	}
}

void AMovingCube::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(GetActorForwardVector() * ForwardSpeed * DeltaTime);
}

void AMovingCube::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (PlayerInputComponent)
	{
		PlayerInputComponent->BindAxis("MoveRight", this, &AMovingCube::MoveRight);
	}
}

void AMovingCube::MoveRight(float Scale)
{
	float DeltaTime = GetWorld()->GetDeltaSeconds();
	AddActorWorldOffset(GetActorRightVector() * Scale * SideSpeed * DeltaTime);
}