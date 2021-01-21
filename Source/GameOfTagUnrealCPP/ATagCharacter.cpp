// Copyright Christopher Buss 2020. Royal Holloway, University of London.

#include "ATagCharacter.h"

#include "Components/BoxComponent.h"
#include "GameOfTagUnrealCPPGameMode.h"
#include "TagAIController.h"
#include "Engine/SkeletalMesh.h"
#include "Animation/AnimBlueprint.h"

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

    // Create a box mesh for tag collisions
    Box = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
    Box->SetRelativeLocation(FVector(45.0f, 0.f, 0.f));
    Box->SetRelativeScale3D(FVector(0.25f, 1.0f, 2.75f));
    Box->SetupAttachment(RootComponent);
    Box->OnComponentBeginOverlap.AddDynamic(
        this, &AATagCharacter::OnBoxBeginOverlap);

    // Set Skeletal Mesh
    static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshContainer(
        TEXT("SkeletalMesh'/Game/Mannequin/Character/"
            "Mesh/SK_Mannequin.SK_Mannequin'"));
    USkeletalMesh* PlayerMesh = static_cast<USkeletalMesh*>(
        MeshContainer.Object);
    GetMesh()->SetSkeletalMesh(PlayerMesh);

    // Set Actor Location and Rotation
    const FVector Location = FVector(0, 0, -90);
    const FRotator Rotation = FRotator(0, -90, 0);
    GetMesh()->SetRelativeLocationAndRotation(Location, Rotation);

    // Set character animations
    static ConstructorHelpers::FObjectFinder<UAnimBlueprint>
        AnimationContainer(
            TEXT("AnimBlueprint'/Game/Mannequin/Animations/"
                "ThirdPerson_AnimBP_C.ThirdPerson_AnimBP_C'"));
    UAnimBlueprint* CharacterAnimation = static_cast<UAnimBlueprint*>(
        AnimationContainer.Object);
    GetMesh()->SetAnimClass(
        CharacterAnimation->GetAnimBlueprintGeneratedClass());

    // Set AI Controller;
    AIControllerClass = ATagAIController::StaticClass();
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
    SetCharacterMaterial();
    GameMode = static_cast<AGameOfTagUnrealCPPGameMode*>(GetWorld()->
        GetAuthGameMode());
    // Creates the delegate to OnItChanged
    GameMode->CallOnItChanged.AddDynamic(this, &AATagCharacter::OnItChanged);
}
