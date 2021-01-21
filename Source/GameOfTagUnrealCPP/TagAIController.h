// Copyright Christopher Buss 2020. Royal Holloway, University of London.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TagAIController.generated.h"

/**
 * Starts the AI Behaviour Tree.
 */
UCLASS()
class GAMEOFTAGUNREALCPP_API ATagAIController final : public AAIController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	UPROPERTY()
	UBlackboardData* BlackboardToUse;
	UPROPERTY()
	UBehaviorTree* BehaviorTreeToUse;
	UPROPERTY()
	UBlackboardComponent* BB;

public:
	ATagAIController();
};
