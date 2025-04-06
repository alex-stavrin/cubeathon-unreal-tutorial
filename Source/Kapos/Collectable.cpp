// Fill out your copyright notice in the Description page of Project Settings.


#include "Collectable.h"
#include "Components/SphereComponent.h"
#include "MovingCube.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"

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
		CollectVolume->OnComponentBeginOverlap.AddDynamic(this, &ACollectable::OnOverlapBegin);
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

void ACollectable::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		AMovingCube* MovingCube = Cast<AMovingCube>(OtherActor);
		if (MovingCube)
		{
			if (CollectSound) UGameplayStatics::PlaySoundAtLocation(GetWorld(), CollectSound, GetActorLocation());
			if (CollectEffect)
			{
				UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), CollectEffect, GetActorLocation(),
					FRotator::ZeroRotator, FVector(1.0f), true, true, ENCPoolMethod::None, true);
			}
;			MovingCube->IncreaseScore();
			Destroy();
		}
	}
}