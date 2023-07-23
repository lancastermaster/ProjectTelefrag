// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/EngineTypes.h"
#include "Math/UnrealMathUtility.h"
#include "Components/BoxComponent.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "TopDownCamera.h"
#include "Particles/ParticleSystem.h"

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
	bCanTelefrag = true;
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CursorToWorldLocation = GetCrosshairWorldPosition();
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Teleport"), EInputEvent::IE_Pressed, this, &APlayerCharacter::LeftMouseDown);
	PlayerInputComponent->BindAction(TEXT("Teleport"), EInputEvent::IE_Released, this, &APlayerCharacter::LeftMouseUp);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &APlayerCharacter::MoveRight);
}

void APlayerCharacter::Teleport()
{
	TArray<AActor*> OverlappingActors;

	FVector TeleportLocation;

	if (bUseMouse)
	{
		TeleportLocation = CursorToWorldLocation;
	}
	else
	{
		TeleportLocation = GetVelocity() * TraceLength;
	}
	TeleportLocation.Z = GetActorLocation().Z;

	FHitResult SweepHit;
	FVector Start = GetActorLocation();
	FVector End = TeleportLocation;
	FQuat Rotation;

	
	bool bObjectinWay = GetWorld()->SweepSingleByChannel(
		SweepHit,
		Start,
		End,
		Rotation,
		ECollisionChannel::ECC_WorldDynamic,
		FCollisionShape::MakeSphere(15.f)
	);

	if (bObjectinWay)
	{

		if (bCanTelefrag)
		{
			SetActorLocation(TeleportLocation);
			GetOverlappingActors(OverlappingActors);

			for (AActor* Actor : OverlappingActors)
			{
				auto Enemy = Cast<AEnemy>(Actor);
				if (Enemy)
				{
					Enemy->Destroy();
					Cast<AEnemyManager>(UGameplayStatics::GetActorOfClass(this, AEnemyManager::StaticClass()))->InitializeLevelEnemies();

					bCanTelefrag = false;
					GetWorldTimerManager().SetTimer(TelefragResetHandle, this, &APlayerCharacter::ResetTelefrag, TelefragResetTime, false);
				}
				else
				{
					SetActorLocation(TeleportLocation, true);
				}
			}

		}
		else
		{
			SetActorLocation(TeleportLocation, true);
			UE_LOG(LogTemp, Warning, TEXT("Telefrag not ready"));
		}
	}
	else
	{
		SetActorLocation(TeleportLocation,true);
	}
}

void APlayerCharacter::CancelTeleport()
{
}

void APlayerCharacter::LeftMouseDown()
{
	bLeftMouseDown = true;
	//UE_LOG(LogTemp, Warning, TEXT("Crosshair World Position: %s"), *CursorToWorldLocation.ToString());
	//spawn targeting FX if you can teleport
}

void APlayerCharacter::LeftMouseUp()
{
	bLeftMouseDown = false;

	Teleport();
	//kill targeting FX
	//teleport if you can
}

void APlayerCharacter::MoveForward(float InputAxis)
{
	AddMovementInput(FVector(1.f, 0.f, 0.f) * InputAxis);
}

void APlayerCharacter::MoveRight(float InputAxis)
{
	AddMovementInput(FVector(0.f, 1.f, 0.f) * InputAxis);
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
	UGameplayStatics::GetPlayerController(this, 0)->GetMousePosition(CursorPosition.X, CursorPosition.Y);
	bool bCursorToWorld = UGameplayStatics::GetPlayerController(this, 0)->GetHitResultUnderCursor(ECollisionChannel::ECC_Visibility, true, ScreenTraceHit);

	
	/*FVector CrosshairWorldPosition;
	FVector CrosshairWorldDirection;

	//Get world position & direction of crosshairs
	bool bScreenToWorld = UGameplayStatics::DeprojectScreenToWorld(
		UGameplayStatics::GetPlayerController(this, 0),
		CursorPosition,
		CrosshairWorldPosition,
		CrosshairWorldDirection);*/

	if (bCursorToWorld)
	{
		//FVector Start{CrosshairWorldPosition};
		//FVector End{ CrosshairWorldPosition + CrosshairWorldDirection * TraceLength };
		
		if (ScreenTraceHit.bBlockingHit)
		{
			OutBeamLocation = ScreenTraceHit.Location;
		}
		/*else
		{
			OutBeamLocation = End;
		}*/

	}
	return OutBeamLocation;
}

