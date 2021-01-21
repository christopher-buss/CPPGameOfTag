// Copyright Christopher Buss 2020. Royal Holloway, University of London.

#pragma once

#include "CoreMinimal.h"

#include "ATagCharacter.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FindTargetToTag.generated.h"

/**
 * Allows for a tagged AI to find a target to move towards to tag
 */
UCLASS()
class GAMEOFTAGUNREALCPP_API
    UBTTask_FindTargetToTag final : public UBTTaskNode {
    GENERATED_BODY()

    virtual EBTNodeResult::Type ExecuteTask(
        UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory
    ) override;

    bool IsPossibleTarget(AActor* Character) const;

    UPROPERTY()
    AGameOfTagUnrealCPPGameMode* GameMode;
};
