// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "TelefragAIController.h"
#include "Components/CapsuleComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.h"
#include "EnemyManager.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();

	EnemyBrain = Cast<ATelefragAIController>(GetController());
	Manager = Cast<AEnemyManager>(UGameplayStatics::GetActorOfClass(this, AEnemyManager::StaticClass()));

	if (BehaviorTree != nullptr) EnemyBrain->RunBehaviorTree(BehaviorTree);
	
}

void AEnemy::SetBlackboardValues()
{
	APlayerCharacter* Player = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));

	bool bSeesPlayer = EnemyBrain->LineOfSightTo(Player, FVector(0.f), false);

	if (bSeesPlayer)
	{
		EnemyBrain->GetBlackboardComponent()->SetValueAsBool(FName("SeesPlayer"), bSeesPlayer);
		EnemyBrain->GetBlackboardComponent()->SetValueAsVector(FName("TargetLocation"), Player->GetActorLocation());
	}
	EnemyBrain->GetBlackboardComponent()->SetValueAsBool(FName("Dying"), bDying);
	EnemyBrain->GetBlackboardComponent()->SetValueAsBool(FName("PlayerDead"), Player->GetPlayerDead());

}

void AEnemy::Move(FVector Destination)
{
	EnemyBrain->MoveToLocation(Destination);
}

void AEnemy::Attack_Implementation()
{
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetBlackboardValues();
}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

