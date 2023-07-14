// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bLeftMouseDown)
	{
		CursorToWorldLocation = GetCrosshairWorldPosition();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Teleport"), EInputEvent::IE_Pressed, this, &APlayerCharacter::LeftMouseDown);
	PlayerInputComponent->BindAction(TEXT("Teleport"), EInputEvent::IE_Released, this, &APlayerCharacter::LeftMouseUp);
}

void APlayerCharacter::Teleport()
{
	FVector TeleportLocation;
	TeleportLocation = CursorToWorldLocation;
	TeleportLocation.Z = GetActorLocation().Z;

	SetActorLocation(TeleportLocation);
}

void APlayerCharacter::CancelTeleport()
{
}

void APlayerCharacter::LeftMouseDown()
{
	bLeftMouseDown = true;
	UE_LOG(LogTemp, Warning, TEXT("Crosshair World Position: %s"), *CursorToWorldLocation.ToString());
	//spawn targeting FX if you can teleport
}

void APlayerCharacter::LeftMouseUp()
{
	bLeftMouseDown = false;

	Teleport();
	//kill targeting FX
	//teleport if you can
}

FVector APlayerCharacter::GetCrosshairWorldPosition()
{
	FHitResult ScreenTraceHit;
	FVector OutBeamLocation;

	FVector2D ViewPortSize;
	if (GEngine && GEngine->GameViewport)
	{
		GEngine->GameViewport->GetViewportSize(ViewPortSize);
	}

	FVector2D CursorPosition;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetMousePosition(CursorPosition.X, CursorPosition.Y);

	//Get screen space location of crosshairs
	FVector2D CrossHairLocation(ViewPortSize.X / 2.f, ViewPortSize.Y / 2.f);
	FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	//Get world position & direction of crosshairs
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CursorPosition,
		CrosshairWorldPosition,
		CrosshairWorldDirection);

	if (bScreenToWorld)
	{
		FVector Start{ CrosshairWorldPosition };
		FVector End{ CrosshairWorldPosition + CrosshairWorldDirection * TraceLength };
		
		if (ScreenTraceHit.bBlockingHit)
		{
			OutBeamLocation = ScreenTraceHit.Location;
		}
		else
		{
			OutBeamLocation = End;
		}

	}
	return OutBeamLocation;
}

