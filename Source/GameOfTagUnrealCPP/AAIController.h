// Copyright Christopher Buss 2020. Royal Holloway, University of London.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AAIController.generated.h"

class UBB_TagAI;

/**
 * 
 */
UCLASS()
class GAMEOFTAGUNREALCPP_API AAAIController : public AAIController {
    GENERATED_BODY()

    // UPROPERTY()
    // UBlackboardComponent* BB;
    // UPROPERTY()
    // UBlackboardComponent* BlackboardComponent;

public:
    AAAIController();

protected:
    virtual void BeginPlay() override;

    // 	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
    // 	UBlackboardData* Blackboard;
    //
    // 	UPROPERTY(EditDefaultsOnly, Category = "Blackboard")
    // 	UBehaviorTree* BehaviorTree;
};
