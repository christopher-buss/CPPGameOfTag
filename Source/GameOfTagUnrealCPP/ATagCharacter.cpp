// Copyright Christopher Buss 2020. Royal Holloway, University of London.


#include "ATagCharacter.h"


#include "AAIController.h"
#include "Components/BoxComponent.h"
#include "GameOfTagUnrealCPPGameMode.h"

AATagCharacter::AATagCharacter() {
    // Gets the default material from game files and creates an instance
    // of the material
    this->Meshes = CreateDefaultSubobject<
        UStaticMeshComponent>(TEXT("Meshes"));
    static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT(
            "Material'/Game/Mannequin/Character/"
            "Materials/M_UE4Man_Body.M_UE4Man_Body'")
    );
    if (Material.Object != nullptr) {
        TheMaterial = static_cast<UMaterial*>(Material.Object);
    }

    // Create a box mesh
    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    /* Set location of mesh */
    Box->SetRelativeLocation(FVector(45.0f, 0.f, 0.f));
    Box->SetRelativeScale3D(FVector(0.25f, 1.0f, 2.75f));
    Box->SetupAttachment(RootComponent);
    /* Attach box collision to function */
    Box->OnComponentBeginOverlap.AddDynamic(
        this, &AATagCharacter::OnBoxBeginOverlap);
}

/**
 * @brief Creates and sets the Characters Material so that the character can
 * change colour when it is tagged 
 */
void AATagCharacter::SetCharacterMaterial() {
    TheMaterial_Dyn = UMaterialInstanceDynamic::Create(TheMaterial, Meshes);
    GetMesh()->SetMaterial(0, TheMaterial_Dyn);
}

/**
* @brief Sets the colour of the character
*
* @param Colour Colour to set the character
*/
void AATagCharacter::SetColour(const FLinearColor Colour) const {
    if (!TheMaterial_Dyn) return;

    TheMaterial_Dyn->SetVectorParameterValue("BodyColor", Colour);
}

/**
* @brief Delegate called when the character who is tagged changes. Used for
* updating the colour of the character when the character is tagged,
* if they become the previous tag, or are no longer the previous tag
*
* @param NewIt The tagged actor
* @param PreviousIt The actor who was tagged previously
*/
void AATagCharacter::OnItChanged(AActor* NewIt, AActor* PreviousIt) {
    if (NewIt == this) {
        SetColour(ItColour);
    } else if (PreviousIt == this) {
        SetColour(PreviousItColour);
    } else {
        SetColour(DefaultItColour);
    }
}

/**
 * @brief Called from Unreal's OnBoxBeginOverlap event. Used to call the Tag
 * function when two actors collide.
 */
void AATagCharacter::OnBoxBeginOverlap(
    UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult
) {
    OtherActor = Cast<AATagCharacter>(OtherActor);
    GameMode->Tag(this, OtherActor);
}

void AATagCharacter::BeginPlay() {
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Begin Play"));
    SetCharacterMaterial();
    GameMode = static_cast<AGameOfTagUnrealCPPGameMode*>(GetWorld()->
        GetAuthGameMode());
    // Creates the delegate to OnItChanged
    GameMode->CallOnItChanged.AddDynamic(this, &AATagCharacter::OnItChanged);
}
