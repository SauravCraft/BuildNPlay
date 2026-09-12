#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BNPGameInstance.generated.h"

UCLASS()
class BUILDNPLAY_API UBNPGameInstance : public UGameInstance
{
    GENERATED_BODY()

public:

    virtual void Init() override;

    virtual void Shutdown() override;
};