// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/GameModeBase.h"
#include "GameOfTagUnrealCPPGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnItChanged, AActor*, It,
                                             AActor*, PreviousIt);

UCLASS()
class AGameOfTagUnrealCPPGameMode final : public AGameModeBase {
    GENERATED_BODY()

    UPROPERTY()
    AActor* It;
    UPROPERTY()
    AActor* PreviousIt;

    void SetFirstTaggedPlayer();
    void Main();

public:
    AGameOfTagUnrealCPPGameMode();
    virtual void BeginPlay() override;

    void Tag(AActor* Tagger, AActor* Tagged);
    UPROPERTY(BlueprintAssignable)
    FOnItChanged CallOnItChanged;
};
