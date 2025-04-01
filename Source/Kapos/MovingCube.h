// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MovingCube.generated.h"

UCLASS()
class KAPOS_API AMovingCube : public APawn
{
	GENERATED_BODY()

public:
	AMovingCube();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* RootMesh;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly)
	float ForwardSpeed = 1500.f;

	UPROPERTY(EditDefaultsOnly)
	float SideSpeed = 500.f;

	UFUNCTION()
	void MoveRight(float Scale);
};
