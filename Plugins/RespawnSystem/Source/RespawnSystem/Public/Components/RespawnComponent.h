#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RespawnComponent.generated.h"

class URespawnSubsystem;

UCLASS(ClassGroup = (Respawn), meta = (BlueprintSpawnableComponent))
class RESPAWNSYSTEM_API URespawnComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    URespawnComponent();

    /** Respawn the owner */
    UFUNCTION(BlueprintCallable, Category = "Respawn")
    void RespawnOwner();

protected:
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    TObjectPtr<URespawnSubsystem> RespawnSubsystem;
};