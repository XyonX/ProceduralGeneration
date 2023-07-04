#include "TopDownGameMode.h"

#include "ProceduralGeneration/Pawn/TopDownPawn.h"
#include "ProceduralGeneration/Player/TopDownPlayerController.h"

ATopDownGameMode::ATopDownGameMode(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	
	DefaultPawnClass=ATopDownPawn::StaticClass();
	PlayerControllerClass=ATopDownPlayerController::StaticClass();
}
