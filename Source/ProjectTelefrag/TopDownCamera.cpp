// Fill out your copyright notice in the Description page of Project Settings.


#include "TopDownCamera.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TelefragPlayerController.h"

// Sets default values
ATopDownCamera::ATopDownCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Root"));
	RootComponent = CameraRoot;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(CameraRoot);

	PlayerTriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Player Trigger Box"));
	PlayerTriggerBox->SetupAttachment(CameraRoot);

}

// Called when the game starts or when spawned
void ATopDownCamera::BeginPlay()
{
	Super::BeginPlay();
	
	PlayerTriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATopDownCamera::OnTriggerOverlap);

	FTimerHandle InitialCameraHandle;
	GetWorldTimerManager().SetTimer(InitialCameraHandle, this, &ATopDownCamera::SetPlayerStartingCamera, .1f, false);
}

void ATopDownCamera::SetPlayerStartingCamera()
{
	TArray<UPrimitiveComponent*> OverlappingComponents;

	auto Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
	Player->GetOverlappingComponents(OverlappingComponents);

	for (UPrimitiveComponent* Comp : OverlappingComponents)
	{
		if (Comp == PlayerTriggerBox)
		{
			Player->SetCurrentCamera(Camera);

			auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
			PlayerController->SetViewTargetWithBlend(this);
		}
	}
}

void ATopDownCamera::OnTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bSweep, const FHitResult& SweepResult)
{
	auto Player = Cast<APlayerCharacter>(OtherActor);

	if (Player)
	{
		Player->SetCurrentCamera(Camera);

		auto PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PlayerController->SetViewTargetWithBlend(this);
	}
}

/*void ATopDownCamera::EndTriggerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor == UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		auto Player = Cast<APlayerCharacter>(OtherActor);
	}
}*/

// Called every frame
void ATopDownCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

