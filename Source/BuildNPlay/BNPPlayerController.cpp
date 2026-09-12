#include "BNPPlayerController.h"

#include "HUD/HUDWidget.h"
#include "Blueprint/UserWidget.h"

void ABNPPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Only create UI for the local player
    if (!IsLocalController())
    {
        return;
    }

    if (!WidgetClass)
    {
        UE_LOG(
            LogTemp,
            Warning,
            TEXT("WidgetClass is not assigned!")
        );

        return;
    }

    HUDWidget = CreateWidget<UHUDWidget>(
        this,
        WidgetClass
    );

    if (HUDWidget)
    {
        HUDWidget->AddToViewport();

        UE_LOG(
            LogTemp,
            Warning,
            TEXT("HUD Widget Created Successfully")
        );
    }
}