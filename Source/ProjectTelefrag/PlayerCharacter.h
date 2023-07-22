// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class PROJECTTELEFRAG_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void Teleport();

	void CancelTeleport();

	void LeftMouseDown();
	void LeftMouseUp();

	void MoveForward(float InputAxis);
	void MoveRight(float InputAxis);

	FVector GetCrosshairWorldPosition();

private:
	class UCameraComponent* CurrentCamera;

	bool bCanTeleport;

	bool bCanTelefrag = true;
	
	bool bLeftMouseDown = false;

	bool bCanMove = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
	bool bUseMouse = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Combat", meta = (AllowPrivateAccess = true))
	bool bDead = false;

	FTimerHandle TelefragResetHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Telefrag", meta = (AllowPrivateAccess = true))
	float TelefragResetTime = 5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
	float TraceLength = 1000.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement", meta = (AllowPrivateAccess = true))
	FVector CursorToWorldLocation;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UCameraComponent* GetCurrentCamera() { return CurrentCamera; }
	void SetCurrentCamera(UCameraComponent* NewCamera) { CurrentCamera = NewCamera; }

	void ResetTelefrag() { bCanTelefrag = true; }

	bool GetPlayerDead() { return bDead; }
};
