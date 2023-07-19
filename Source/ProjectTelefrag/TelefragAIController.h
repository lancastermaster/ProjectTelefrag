// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TelefragAIController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTTELEFRAG_API ATelefragAIController : public AAIController
{
	GENERATED_BODY()
	
	public:
		ATelefragAIController();

		virtual void OnPossess(APawn* InPawn) override;
	protected:

	private:
		UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true))
			class UBlackboardComponent* BlackboardComp;

		UPROPERTY(BlueprintReadWrite, Category = "AI Behavior", meta = (AllowPrivateAccess = true))
			class UBehaviorTreeComponent* BehaviorTreeComp;


	public:
	FORCEINLINE UBlackboardComponent* GetBlackboardComponent() const { return BlackboardComp; }
};
