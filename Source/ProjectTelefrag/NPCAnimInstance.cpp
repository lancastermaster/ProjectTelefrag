// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

void UNPCAnimInstance::UpdateAnimationProperties(float DeltaTime)
{
    if (NPC == nullptr) NPC = Cast<ACharacter>(TryGetPawnOwner());

    if (NPC)
    {
        FVector Velocity{ NPC->GetVelocity() };
        Velocity.Z = 0.f;
        Speed = Velocity.Size();

        bInAir = NPC->GetMovementComponent()->IsFalling();
    }
}
