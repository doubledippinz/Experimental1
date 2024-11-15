#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "CommonUI/Public/CommonActivatableWidget.h"
#include "Widgets/CommonActivatableWidgetContainer.h"
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01-UI")
    TSubclassOf<UUserWidget> WidgetClass;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "01-UI")
    TSubclassOf<UCommonActivatableWidgetContainerBase> ActivatableWidgetContainer;


private:
    void PauseGame(const FInputActionValue& Value);
    void ShowPauseMenu();
    void RemovePauseMenu();



    UUserWidget* WidgetInstance;
};
