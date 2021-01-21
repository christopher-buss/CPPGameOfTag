// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameOfTagUnrealCPPGameMode.h"

#include "ATagCharacter.h"
#include "ATagPlayer.h"
#include "Kismet/GameplayStatics.h"

/**
 * @brief Gets all the AI actors and sets the first found actor as "It"
 */
void AGameOfTagUnrealCPPGameMode::SetFirstTaggedPlayer() {
    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsOfClass(
        GetWorld(), AATagCharacter::StaticClass(), FoundActors);
    It = FoundActors[0];
}

/**
 * @brief Sets default pawn class to our character
 */
AGameOfTagUnrealCPPGameMode::AGameOfTagUnrealCPPGameMode() {
    DefaultPawnClass = AATagPlayer::StaticClass();
}

/**
 * @brief Sets the new tagged player, and stores the current tagged player
 * as the previous it.
 * @param Tagger The current tagged player
 * @param Tagged The new tagged player
 */
void AGameOfTagUnrealCPPGameMode::Tag(AActor* Tagger, AActor* Tagged) {
    if (Tagger == It && Tagged != PreviousIt) {
        PreviousIt = It;
        It = Tagged;
        CallOnItChanged.Broadcast(It, PreviousIt);
    }
}

void AGameOfTagUnrealCPPGameMode::Main() {
    SetFirstTaggedPlayer();
    CallOnItChanged.Broadcast(It, nullptr);
}

void AGameOfTagUnrealCPPGameMode::BeginPlay() {
    Super::BeginPlay();
    FTimerHandle UnusedHandle;
    // Add delay to ensure the CallOnItChanged Delegate is present
    GetWorldTimerManager().SetTimer(
        UnusedHandle, this, &AGameOfTagUnrealCPPGameMode::Main, 0.1, false);
}
