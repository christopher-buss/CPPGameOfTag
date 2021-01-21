// Copyright Christopher Buss 2020. Royal Holloway, University of London.

#include "AIController.h"
#include "BTTask_FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

/**
 * @brief Finds a random location in the world, and then sets the blackboard
 * value "TargetLocation" to that random location
 * @return EBTNodeResult: Code if task executes successfully or not
 */
EBTNodeResult::Type UBTTask_FindRandomLocation::ExecuteTask(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory
) {
    if (!(OwnerComp.GetAIOwner() && OwnerComp.GetAIOwner()->GetPawn())) {
        return EBTNodeResult::Failed;
    }
    // Get the AI pawn (self)
    APawn* ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
    UNavigationSystemV1* NavSystem = Cast<UNavigationSystemV1>(
        GetWorld()->GetNavigationSystem());
    
    if (!ControlledPawn || !NavSystem) return EBTNodeResult::Failed;

    FNavLocation RandomLocation;
    NavSystem->GetRandomPointInNavigableRadius(
        ControlledPawn->GetActorLocation(), 6000.0f, RandomLocation);
    // Set blackboard value to found random location
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(
        FName("TargetLocation"), RandomLocation);
    return EBTNodeResult::Succeeded;
}
