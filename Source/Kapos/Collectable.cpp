// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"
#include "Components/SphereComponent.h"

ACollectable::ACollectable()
{
	PrimaryActorTick.bCanEverTick = true;

	RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RootMesh"));
	if (RootMesh)
	{
		SetRootComponent(RootMesh);
	}

	CollectVolume = CreateDefaultSubobject<USphereComponent>(TEXT("CollectVolume"));
	if (CollectVolume)
	{
		CollectVolume->SetupAttachment(RootMesh);
	}
}

void ACollectable::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACollectable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

