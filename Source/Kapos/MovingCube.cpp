// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingCube.h"
#include "Camera/CameraComponent.h"

// Sets default values
AMovingCube::AMovingCube()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
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

// Called when the game starts or when spawned
void AMovingCube::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMovingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(GetActorForwardVector() * 500.f * DeltaTime);
}

// Called to bind functionality to input
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
	AddActorWorldOffset(GetActorRightVector() * Scale * 500.f * DeltaTime);
}

