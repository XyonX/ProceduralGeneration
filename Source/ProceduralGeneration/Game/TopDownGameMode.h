#pragma once

#include "GameFramework/GameMode.h"
#include "TopDownGameMode.generated.h"


UCLASS(Blueprintable)
class PROCEDURALGENERATION_API ATopDownGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATopDownGameMode(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};