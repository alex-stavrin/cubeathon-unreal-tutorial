// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/WidgetComponent.h"
#include "Movable.generated.h"

UCLASS()
class KAPOS_API AMovable : public AActor
{
    GENERATED_BODY()

public:
    AMovable();

protected:
    virtual void BeginPlay() override;

public:
    virtual void Tick(float DeltaTime) override;

    UPROPERTY(VisibleAnywhere)
    UStaticMeshComponent* RootMesh;

    UPROPERTY(EditAnywhere, meta = (MakeEditWidget = true))
    FVector EndPosition;

    UPROPERTY(EditAnywhere)
    float MoveSpeed;

private:
    FVector StartPosition;
    float Progress;
    bool bMovingToEnd;
};
