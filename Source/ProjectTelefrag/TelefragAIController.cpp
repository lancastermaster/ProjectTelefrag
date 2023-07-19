// Fill out your copyright notice in the Description page of Project Settings.


#include "TelefragAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Enemy.h"

ATelefragAIController::ATelefragAIController()
{
    BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("Blackboard Component"));
    check(BlackboardComp);

    BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("Behavior Tree Component"));
    check(BehaviorTreeComp);
}

void ATelefragAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    if (InPawn == nullptr)return;

    AEnemy* Enemy = Cast<AEnemy>(InPawn);
    if (Enemy)
    {
        if (Enemy->GetBehaviorTree())
        {
            BlackboardComp->InitializeBlackboard(*(Enemy->GetBehaviorTree()->BlackboardAsset));
        }
    }
}
