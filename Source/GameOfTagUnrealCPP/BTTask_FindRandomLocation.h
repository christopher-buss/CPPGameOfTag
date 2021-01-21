// Copyright Christopher Buss 2020. Royal Holloway, University of London.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindRandomLocation.generated.h"

/**
 * Finds a random location for an AI character to move to.
 */
UCLASS()
class GAMEOFTAGUNREALCPP_API
    UBTTask_FindRandomLocation final : public UBTTaskNode {
    GENERATED_BODY()

    virtual EBTNodeResult::Type ExecuteTask(
        UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory
    ) override;
};
