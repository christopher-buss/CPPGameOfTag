// Copyright Christopher Buss 2020. Royal Holloway, University of London.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CheckWhoIsIt.generated.h"

/**
 * Class to check which character is tagged.
 */
UCLASS()
class GAMEOFTAGUNREALCPP_API UCheckWhoIsIt final : public UBTService {
    GENERATED_BODY()

    virtual void TickNode(
        UBehaviorTreeComponent & OwnerComp,
        uint8 * NodeMemory,
        float DeltaSeconds
    ) override;

    UPROPERTY()
    APawn* ControlledPawn;
};
