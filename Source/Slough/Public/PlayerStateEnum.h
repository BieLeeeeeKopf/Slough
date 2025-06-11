#pragma once

#include "CoreMinimal.h"
#include "PlayerStateEnum.generated.h"

UENUM(BlueprintType) 
enum class EPlayerStateEnum : uint8
{
    Idle        UMETA(DisplayName = "Idle"),
    Walking     UMETA(DisplayName = "Walking"),
    Running     UMETA(DisplayName = "Running"),
    Jumping     UMETA(DisplayName = "Jumping"),
    Attacking   UMETA(DisplayName = "Attacking"),
    Reloading   UMETA(DisplayName = "Reloading"),
    Dead        UMETA(DisplayName = "Dead")
};