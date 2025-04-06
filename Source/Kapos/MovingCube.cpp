#include "MovingCube.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"


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
	
	OnActorHit.AddDynamic(this, &AMovingCube::OnHit);

	if(PlayerWidgetClass)
	{ 
		PlayerWidget =  CreateWidget<UPlayerWidget>(GetWorld(), PlayerWidgetClass);
		if (PlayerWidget)
		{
			PlayerWidget->AddToViewport();
			PlayerWidget->ScoreText->SetText(FText::AsNumber(0));
		}
	}
}

void AMovingCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldOffset(GetActorForwardVector() * ForwardSpeed * DeltaTime);

	if (GetActorLocation().Z <= FallZ)
	{
		RestartLevel();
	}
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

void AMovingCube::OnHit(AActor* SelfActor, AActor* OtherActor, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor)
	{
		if (OtherActor->ActorHasTag("Obstacle"))
		{
			RestartLevel();
		}
	}
}

void AMovingCube::RestartLevel()
{
	FString CurrentLevelName = GetWorld()->GetName();
	UGameplayStatics::OpenLevel(GetWorld(), *CurrentLevelName);
}

void AMovingCube::IncreaseScore()
{
	score++;
	if (PlayerWidget)
	{
		PlayerWidget->ScoreText->SetText(FText::AsNumber(score));
	}
}