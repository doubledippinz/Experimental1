#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UUserWidget;
class UWidget;
class UPanelWidget;

UCLASS()
class EXPERIMENTAL_API AMyPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    AMyPlayerController();

protected:
    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputMappingContext* InputMappingContext;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputAction* PauseAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputAction* MenuUpAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputAction* MenuDownAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputAction* MenuLeftAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputAction* MenuRightAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputAction* MenuSelectAction;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
    UInputAction* MenuBackAction;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "02-HUD")
    TSubclassOf<UUserWidget> PauseMenuWidgetClass;

private:
    void PauseGame(const FInputActionValue& Value);
    void ShowPauseMenu();
    void RemovePauseMenu();
    void NavigateUp(const FInputActionValue& Value);
    void NavigateDown(const FInputActionValue& Value);
    void NavigateLeft(const FInputActionValue& Value);
    void NavigateRight(const FInputActionValue& Value);
    void Confirm(const FInputActionValue& Value);
    void MenuBack(const FInputActionValue& Value);

    void SetUserFocusToNextWidget(UWidget* CurrentWidget, EUINavigation NavigationDirection);
    UWidget* GetFocusedWidget();


    UUserWidget* PauseMenuWidgetInstance;
};
