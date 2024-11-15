#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AMyPlayerController::AMyPlayerController()
{
    // Constructor logic here if needed
}

void AMyPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
    {
        Subsystem->AddMappingContext(InputMappingContext, 0);
    }
}
void AMyPlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
    {
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Triggered, this, &AMyPlayerController::PauseGame);
    }
}

void AMyPlayerController::PauseGame(const FInputActionValue& Value)
{
    const bool CurrentValue = Value.Get<bool>();

    if (CurrentValue)
    {
        // Toggle game paused state
        bool bIsPaused = UGameplayStatics::IsGamePaused(GetWorld());
        UGameplayStatics::SetGamePaused(GetWorld(), !bIsPaused);
    }
}

void AMyPlayerController::ShowPauseMenu()
{
    if (WidgetClass)
    {
        WidgetInstance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);

        if (WidgetInstance)
        {
            WidgetInstance->AddToViewport(999);
            // Set input mode to Game and UI
            FInputModeGameAndUI InputMode;
            InputMode.SetWidgetToFocus(WidgetInstance->TakeWidget());
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            SetInputMode(InputMode);
            bShowMouseCursor = true;  // Show mouse cursor if needed
            WidgetInstance->SetKeyboardFocus();  // Set keyboard focus
        }
    }
}


void AMyPlayerController::RemovePauseMenu()
{
    WidgetInstance->RemoveFromParent();
}


