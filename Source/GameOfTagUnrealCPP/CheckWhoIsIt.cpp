// Copyright Christopher Buss 2020. Royal Holloway, University of London.


#include "CheckWhoIsIt.h"

#include "AIController.h"
#include "GameOfTagUnrealCPPGameMode.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

/**
* @brief Checks if the AI character is tagged, and if they are, sets the
* blackboard value "IAmIt" to true. If not, sets to false.
 */
void UCheckWhoIsIt::TickNode(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds
) {
    // Tick every 0.1 seconds
    SetNextTickTime(NodeMemory, 0.1f);
    // Get the blackboard
    UBlackboardComponent* CurrentBlackboard = OwnerComp.
        GetBlackboardComponent();
    if (OwnerComp.GetAIOwner() && OwnerComp.GetAIOwner()->GetPawn()) {
        ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
    }
    AGameOfTagUnrealCPPGameMode* GameMode = Cast<AGameOfTagUnrealCPPGameMode>(
        UGameplayStatics::GetGameMode(GetWorld()));
    if (ControlledPawn == GameMode->It) {
        // Sets the blackboard value
        CurrentBlackboard->SetValueAsBool(FName("IAmIt"), true);
    } else {
        CurrentBlackboard->SetValueAsBool(FName("IAmIt"), false);
    }
}
