#include "EndVolume.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

AEndVolume::AEndVolume()
{
	PrimaryActorTick.bCanEverTick = true;

	Volume = CreateDefaultSubobject<UBoxComponent>(TEXT("Volume"));
	if (Volume)
	{
		SetRootComponent(Volume);
	}
}

void AEndVolume::BeginPlay()
{
	Super::BeginPlay();

	if (Volume)
	{
		Volume->OnComponentBeginOverlap.AddDynamic(this, &AEndVolume::OnOverlapBegin);
	}
	
}

void AEndVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEndVolume::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		UGameplayStatics::OpenLevel(GetWorld(), NextLevel);
	}
}
