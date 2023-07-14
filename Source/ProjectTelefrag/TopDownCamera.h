// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TopDownCamera.generated.h"

UCLASS()
class PROJECTTELEFRAG_API ATopDownCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATopDownCamera();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetPlayerStartingCamera();

	UFUNCTION()
		void OnTriggerOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bSweep,
			const FHitResult& SweepResult);

	/*UFUNCTION()
		void EndTriggerOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex);*/

private:

	class USceneComponent* CameraRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	class UBoxComponent* PlayerTriggerBox;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
