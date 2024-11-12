#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class UUserWidget;

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
    void MenuUp(const FInputActionValue& Value);
    void MenuDown(const FInputActionValue& Value);
    void MenuLeft(const FInputActionValue& Value);
    void MenuRight(const FInputActionValue& Value);
    void MenuSelect(const FInputActionValue& Value);
    void MenuBack(const FInputActionValue& Value);

    UUserWidget* PauseMenuWidgetInstance;

    UUserWidget* PauseMenuWidgetInstance; 
    UWidget* GetFocusedWidget(); 
    UWidget* FindNextWidget(UWidget* CurrentWidget, ENavigationDirection Direction)

    // Add member variables to keep track of selected menu item
    int32 CurrentMenuIndex;
    TArray<UUserWidget*> MenuItems; // Assumes menu items are UserWidgets
};
