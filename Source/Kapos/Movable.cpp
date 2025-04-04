#include "Movable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"

AMovable::AMovable()
{
    PrimaryActorTick.bCanEverTick = true;

    RootMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    if (RootMesh)
    {
        SetRootComponent(RootMesh);
    }
}

void AMovable::BeginPlay()
{
    Super::BeginPlay();
    Progress = 0.f;
    bMovingToEnd = true;
    StartPosition = GetActorLocation();

    // Convert end position to world
    EndPosition = GetActorTransform().TransformPosition(EndPosition);
}

void AMovable::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (bMovingToEnd)
    {
        Progress += DeltaTime;

        if (Progress >= 1)
        {
            bMovingToEnd = false;
        }
    }

    if(!bMovingToEnd)
    {
        Progress -= DeltaTime;
        
        if (Progress <= 0)
        {
            bMovingToEnd = true;
        }
    }
    FVector NewLocation = FMath::Lerp(StartPosition, EndPosition, Progress);

    SetActorLocation(NewLocation);
}