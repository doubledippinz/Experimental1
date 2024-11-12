#include "MyPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include <Kismet/GameplayStatics.h>
#include <Components/PanelWidget.h>
#include <Components/Widget.h>
#include <Blueprint/WidgetBlueprintLibrary.h>



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
        EnhancedInputComponent->BindAction(MenuLeftAction, ETriggerEvent::Triggered, this, &AMyPlayerController::NavigateLeft);
        EnhancedInputComponent->BindAction(MenuDownAction, ETriggerEvent::Triggered, this, &AMyPlayerController::NavigateDown);
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

            // Set input mode to Game and UI
            FInputModeGameAndUI InputMode;
            InputMode.SetWidgetToFocus(PauseMenuWidgetInstance->TakeWidget());
            InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
            SetInputMode(InputMode);

            bShowMouseCursor = true;  // Show mouse cursor if needed
            PauseMenuWidgetInstance->SetKeyboardFocus();  // Set keyboard focus

            UE_LOG(LogTemp, Warning, TEXT("Pause menu shown and input mode set."));
        }
    }
}

void AMyPlayerController::RemovePauseMenu()
{
    if (PauseMenuWidgetInstance && PauseMenuWidgetInstance->IsInViewport())
    {
        PauseMenuWidgetInstance->RemoveFromParent();
        PauseMenuWidgetInstance = nullptr;

        // Set input mode back to Game Only
        FInputModeGameOnly InputMode;
        SetInputMode(InputMode);

        bShowMouseCursor = false;  // Hide mouse cursor

        UE_LOG(LogTemp, Warning, TEXT("Pause menu removed and input mode set to Game Only."));
    }
}



void AMyPlayerController::NavigateDown(const FInputActionValue& Value)
{
    UWidget* CurrentFocusedWidget = GetFocusedWidget();
    if (CurrentFocusedWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("Navigate Down triggered."));
        SetUserFocusToNextWidget(CurrentFocusedWidget, EUINavigation::Down);
    }
}

void AMyPlayerController::NavigateLeft(const FInputActionValue& Value)
{
    UWidget* CurrentFocusedWidget = GetFocusedWidget();
    if (CurrentFocusedWidget)
    {
        UE_LOG(LogTemp, Warning, TEXT("Navigate Left triggered."));
        SetUserFocusToNextWidget(CurrentFocusedWidget, EUINavigation::Left);
    }
}



void AMyPlayerController::SetUserFocusToNextWidget(UWidget* CurrentWidget, EUINavigation NavigationDirection)
{
    if (!CurrentWidget || !PauseMenuWidgetInstance)
    {
        return;
    }

    UPanelWidget* ParentWidget = Cast<UPanelWidget>(CurrentWidget->GetParent());
    if (ParentWidget)
    {
        int32 CurrentIndex = ParentWidget->GetChildIndex(CurrentWidget);
        int32 NextIndex = -1;

        if (NavigationDirection == EUINavigation::Down)
        {
            NextIndex = CurrentIndex + 1;
        }
        else if (NavigationDirection == EUINavigation::Left)
        {
            NextIndex = CurrentIndex - 1;
        }
        else if (NavigationDirection == EUINavigation::Up)
        {
            NextIndex = CurrentIndex - 1;
        }
        else if (NavigationDirection == EUINavigation::Right)
        {
            NextIndex = CurrentIndex + 1;
        }

        if (NextIndex >= 0 && NextIndex < ParentWidget->GetChildrenCount())
        {
            UWidget* NextWidget = ParentWidget->GetChildAt(NextIndex);
            if (NextWidget)
            {
                NextWidget->SetUserFocus(this);
                NextWidget->SetKeyboardFocus();  // Explicitly set keyboard focus for the next widget
                UE_LOG(LogTemp, Warning, TEXT("Focused widget changed to: %s"), *NextWidget->GetName());
            }
        }
    }
}

UWidget* AMyPlayerController::GetFocusedWidget()
{
    TArray<UUserWidget*> AllWidgets;
    UWidgetBlueprintLibrary::GetAllWidgetsOfClass(this, AllWidgets, UUserWidget::StaticClass(), false);

    for (UUserWidget* Widget : AllWidgets)
    {
        if (Widget->HasAnyUserFocus())
        {
            UE_LOG(LogTemp, Warning, TEXT("Currently focused widget: %s"), *Widget->GetName());
            return Widget;
        }
    }
    return nullptr;
}
















