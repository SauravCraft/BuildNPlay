#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BNPPlayerController.generated.h"

class UHUDWidget;

UCLASS()
class BUILDNPLAY_API ABNPPlayerController : public APlayerController
{
    GENERATED_BODY()

public:

    virtual void BeginPlay() override;

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    TSubclassOf<UHUDWidget> WidgetClass;

    UPROPERTY()
    TObjectPtr<UHUDWidget> HUDWidget;
};