// Copyright Christopher Buss 2020. Royal Holloway, University of London.

#include "BTTask_FindTargetToTag.h"

#include "AIController.h"
#include "ATagCharacter.h"
#include "GameOfTagUnrealCPPGameMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

/**
 * @brief Iterates through an array of all actors in the game, checks if
 * they're a possible target, and then sets the "TargetActor" blackboard to
 * the found actor
 * @return EBTNodeResult: Code if task executes successfully or otherwise
 */
EBTNodeResult::Type UBTTask_FindTargetToTag::ExecuteTask(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory
) {
    if (!(OwnerComp.GetAIOwner() && OwnerComp.GetAIOwner()->GetPawn())) {
        return EBTNodeResult::Failed;
    }
    // Get the AI pawn (self)
    APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
    GameMode = Cast<AGameOfTagUnrealCPPGameMode>(
        UGameplayStatics::GetGameMode(GetWorld()));

    // Get all actors in the world
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(), AATagCharacter::StaticClass(), FoundActors);

    const float MinDistance = 10000000.0f;
    AActor* TagCandidate = nullptr;

    for (AActor* Actor : FoundActors) {
        if (IsPossibleTarget(Actor)) {
            if (Actor->GetDistanceTo(ControlledPawn) <= MinDistance) {
                TagCandidate = Actor;
            }
        }
    }
    // Set blackboard value
    OwnerComp.GetBlackboardComponent()->SetValueAsObject(
        FName("TargetActor"), TagCandidate);
    return EBTNodeResult::Succeeded;
}

/**
 * @brief Checks if the found actor is not "It", and not the "PreviousIt". If
 * true then they are a possible target
 * @param Character: The actor to compare
 * @return bool: true if possible target
 */
bool UBTTask_FindTargetToTag::IsPossibleTarget(AActor* Character) const {
    return Character != GameMode->It && Character != GameMode->PreviousIt;
}
