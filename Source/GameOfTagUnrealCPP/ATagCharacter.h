// Copyright Christopher Buss 2020. Royal Holloway, University of London.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "ATagCharacter.generated.h"


class AGameOfTagUnrealCPPGameMode;
class UBoxComponent;

/**
 * An actor that holds all data for character interactions in a game of tag
 */
UCLASS()
class GAMEOFTAGUNREALCPP_API AATagCharacter : public ACharacter {
    GENERATED_BODY()

    void SetCharacterMaterial();
    void SetColour(FLinearColor Colour) const;

    FLinearColor ItColour = FLinearColor(0.3, 0.01, 0.01, 0);
    FLinearColor PreviousItColour = FLinearColor(0.63, 0.56, 0, 0);
    FLinearColor DefaultItColour = FLinearColor(0.27, 0.27, 0.27, 0);

public:
    AATagCharacter();

    UFUNCTION()
    void OnItChanged(AActor* NewIt, AActor* PreviousIt);

    UPROPERTY(Category=Character, VisibleAnywhere, BlueprintReadOnly, meta=(
        AllowPrivateAccess = "true"))
    UBoxComponent* Box = nullptr;

    UFUNCTION()
    void OnBoxBeginOverlap(
        UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
        const FHitResult& SweepResult
    );

protected:
    virtual void BeginPlay() override;

    UPROPERTY()
    UMaterialInstanceDynamic* TheMaterial_Dyn = nullptr;
    UPROPERTY()
    UMaterial* TheMaterial = nullptr;
    UPROPERTY()
    UStaticMeshComponent* Meshes = nullptr;
    UPROPERTY()
    AGameOfTagUnrealCPPGameMode* GameMode = nullptr;
};
