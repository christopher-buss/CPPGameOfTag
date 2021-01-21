// Copyright Christopher Buss 2020. Royal Holloway, University of London.

#include "TagAIController.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BehaviorTree.h"

/**
 * @brief Gets Blackboard and Behaviour Tree from files
 */
ATagAIController::ATagAIController() {
    static ConstructorHelpers::FObjectFinder<UBlackboardData> FindBlackboard(
        TEXT("BlackboardData'/Game/ThirdPersonCPP/"
            "Blueprints/BB_TagAI.BB_TagAI'"));
    BlackboardToUse = Cast<UBlackboardData>(FindBlackboard.Object);

    static ConstructorHelpers::FObjectFinder<UBehaviorTree> FindBT(TEXT(
        "BehaviorTree'/Game/ThirdPersonCPP/Blueprints/BT_TagAI.BT_TagAI'"));
    BehaviorTreeToUse = Cast<UBehaviorTree>(FindBT.Object);
}

/**
 * @brief Tells the AI which blackboard to use, and to run the Behaviour Tree
 */
void ATagAIController::BeginPlay() {
    Super::BeginPlay();

    UseBlackboard(BlackboardToUse, BB);
    RunBehaviorTree(BehaviorTreeToUse);
}
