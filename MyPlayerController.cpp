#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include <Kismet/GameplayStatics.h>

AMyPlayerController::AMyPlayerController()
    : PauseMenuWidgetInstance(nullptr) // Initialize the widget instance to nullptr
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

        if (!bIsPaused) // Game is now paused
        {
            ShowPauseMenu();
        }
        else // Game is now unpaused
        {
            RemovePauseMenu();
        }
    }
}

void AMyPlayerController::ShowPauseMenu()
{
    if (PauseMenuWidgetClass)
    {
        PauseMenuWidgetInstance = CreateWidget<UUserWidget>(GetWorld(), PauseMenuWidgetClass);
        if (PauseMenuWidgetInstance)
        {
            PauseMenuWidgetInstance->AddToViewport(999);
            FInputModeGameAndUI InputMode; // Use Game and UI mode
            InputMode.SetWidgetToFocus(PauseMenuWidgetInstance->TakeWidget());
            SetInputMode(InputMode);
            bShowMouseCursor = true;
        }
    }
}

void AMyPlayerController::RemovePauseMenu()
{
    if (PauseMenuWidgetInstance && PauseMenuWidgetInstance->IsInViewport())
    {
        PauseMenuWidgetInstance->RemoveFromParent();
        PauseMenuWidgetInstance = nullptr;
        FInputModeGameOnly InputMode;
        SetInputMode(InputMode);
        bShowMouseCursor = false;
    }
}

void AMyPlayerController::MenuUp(const FInputActionValue& Value)
{
    // Logic to navigate up in the widget hierarchy
    UWidget* CurrentFocusedWidget = GetFocusedWidget(); 
    if (CurrentFocusedWidget) 
    { UWidget* NextWidget = FindNextWidget(CurrentFocusedWidget, ENavigationDirection::Up); 
    if (NextWidget) 
    { NextWidget->SetUserFocus(GetLocalPlayer());
}

void AMyPlayerController::MenuDown(const FInputActionValue& Value)
{
}

void AMyPlayerController::MenuLeft(const FInputActionValue& Value)
{
}

void AMyPlayerController::MenuRight(const FInputActionValue& Value)
{
}

void AMyPlayerController::MenuSelect(const FInputActionValue& Value)
{
}

void AMyPlayerController::MenuBack(const FInputActionValue& Value)
{
}

UWidget* AMyPlayerController::GetFocusedWidget()
{
    if (PauseMenuWidgetInstance)
    {
        return PauseMenuWidgetInstance->GetWidget()->GetFocusedWidget();
    }
    return nullptr;
}

UWidget* AMyPlayerController::FindNextWidget(UWidget* CurrentWidget, ENavigationDirection Direction)
{ 
    if (CurrentWidget && PauseMenuWidgetInstance) 
    { 
        UWidget* NextWidget = CurrentWidget->Navigate(Direction); 
        return NextWidget; 
    } return nullptr; 
}
