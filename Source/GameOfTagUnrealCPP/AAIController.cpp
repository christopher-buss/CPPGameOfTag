// Copyright Christopher Buss 2020. Royal Holloway, University of London.


#include "AAIController.h"


#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

AAAIController::AAAIController() {
	UE_LOG(LogTemp, Warning, TEXT("Controlled Initialised"));
	// Blackboard = NewObject<UBlackboardData>();
	// Blackboard->UpdatePersistentKey<UBlackboardKeyType_Object>(FName("Target"));
 //
	// BlackboardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComponent"));
}

void AAAIController::BeginPlay() {
	// Super::BeginPlay();
	// if (!ensure(Blackboard)) return;
	// UseBlackboard(Blackboard, BB);
	// if (!ensure(BehaviorTree)) return;
	// RunBehaviorTree(BehaviorTree);
}
