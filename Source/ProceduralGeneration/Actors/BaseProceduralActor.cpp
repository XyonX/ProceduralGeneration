// Fill out your copyright notice in the Description page of Project Settings.
#include "BaseProceduralActor.h"

#include "../../../../../../../UE_5.1/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "Components/InstancedStaticMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "ProceduralGeneration/Debugging/CoreDebugContainer.h"
#include "Containers/Array.h"
#include "ProceduralGeneration/Tiles/Tile.h"
#include  "ProceduralGeneration/TileMesh/TileMesh.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
//#include "ProceduralGenerationEditor/DockTab/GenerationControllerTab.h"
#include "InputMappingContext.h"
#include "EnhancedInputModule.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "Engine/LocalPlayer.h"

#define LogSwitch 1

TSharedPtr<SWindow> ABaseProceduralActor::ControllerWindow;
FOnGenerateButtonClick ABaseProceduralActor::GenerateClickDelegate_Actor;
// CONSTRUCTOR
ABaseProceduralActor::ABaseProceduralActor()
{
	// TURNING OFF TICK
	PrimaryActorTick.bCanEverTick = false;
	
	// CREATING  INSTANCE MESH FOR BASE FLOOR 
	FlorInstanceMeshComponent= CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("TileMesh"));

	// SETTING THE ALL TILE FLOAT COUNTER TO 0
	AllTiles_Float = 0 ;

	//Settign default tile Length
	Actor_Length_X = 200;
	Actor_Length_Y = 200;
	Actor_Length_Z = 200 ;

	bWantCustomTileSize =false;
	
	//Setting up Default tile mesh
	//DefaultInstanceMeshComponent = CreateDefaultSubobject<UInstancedStaticMeshComponent>(TEXT("DEFAULT MESH INSTANCE CONTAINER"));
	
	
	//SETTING UP DEFAULT TILE
	DefaultTile = CreateDefaultSubobject<UTile>("DefaultTile");
	DefaultTileMesh=CreateDefaultSubobject<UTileMesh>("DefaultTileMesh");
	DefaultTile->World_Location=FVector(0.0f,0.0f,100.0f);
	DefaultTile->Position_2D=FMatrixPosition(0,0);
	DefaultTile->SelectedTiledMesh = DefaultTileMesh ;
	
	//static ConstructorHelpers::FObjectFinder<UDataTable> TileMeshDataAssetObject(TEXT("DataTable'/ProceduralGeneration/Data/DT_TileMesh.DT_TileMesh'"));
	static ConstructorHelpers::FObjectFinder<UDataTable> TileMeshDataAssetObject(TEXT("DataTable'/ProceduralGeneration/Data/DT_TileMesh.DT_TileMesh'"));

	if (TileMeshDataAssetObject.Succeeded())
	{
		TileMeshDataAsset = TileMeshDataAssetObject.Object;
	}
	
}


//BEGIN PLAY
void ABaseProceduralActor::BeginPlay()
{
	Super::BeginPlay();

	SetupInput();

	//init the class
	Init();

	//GENERATING TILE
	CalculateMeshLength();
	GenerateTile();
	SetTileLength(Actor_Length_X,Actor_Length_Y);
	GenerateBaseFloor(AllTilesPTR);
	
	if (!AllTilesPTR.IsEmpty() && !TotalTileMesh.IsEmpty())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT(" BOTH TILE AND TOTAL MESH AVAILABLE WAVE FUNCTION CALLING  "));
		}

		// STARTING THE MAIN ALGORITHM
		WaveFunctionCollapse();
		bIsFirstGenDone=true;
	}
	else
	{
		// error occurred, display an error message
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Could not generate tile or total mesh. Aborting."));
		}
	}
}

void ABaseProceduralActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	for (int32 i = AllTilesPTR.Num() - 1; i >= 0; i--)
	{
		UTile* Tile = AllTilesPTR[i];
		Tile->ConditionalBeginDestroy();
		AllTilesPTR.RemoveAt(i);
		RemainingTiles.Remove(Tile);
		CollapsedTiles.Remove(Tile);
		
	}
	for(int32 j = TotalTileMesh.Num()-1 ; j>= 0 ; j--)
	{
		UTileMesh* TileMesh =TotalTileMesh[j];
		TileMesh->ConditionalBeginDestroy();
		TotalTileMesh.RemoveAt(j);
	}
	AllTilesPTR.Empty();
	RemainingTiles.Empty();
	CollapsedTiles.Empty();
	TotalTileMesh.Empty();

	

	if(DefaultTile != nullptr)
	{
		DefaultTile->ConditionalBeginDestroy();
		DefaultTile=nullptr;
	}
	if(DefaultTileMesh != nullptr)
	{
		DefaultTileMesh->ConditionalBeginDestroy();
		DefaultTileMesh = nullptr ;
	}

	if (ControllerWindow.IsValid() && ControllerWindow->IsVisible())
	{
		// The window is already visible, so just hide it
		ControllerWindow->HideWindow();
		FSlateApplication::Get().DestroyWindowImmediately(ControllerWindow.ToSharedRef());
		ControllerWindow.Reset();
	}
	
}

void ABaseProceduralActor::SetupInput()
{
	
	// Get the player controller
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (!PlayerController)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Controller Not found "));}
		return;
	}

	// Get the enhanced input subsystem for the local player
	ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	if (!LocalPlayer)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Local player Not found "));}
		return;
	}

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputModule = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	if(!EnhancedInputModule)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Enhancce input subsystem not fofund "));}
		return;
	}
	
	if(!ProceduralGenerationMapping )
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Maping  context  not fofund "));}
		return;
	}
	EnhancedInputModule->AddMappingContext(ProceduralGenerationMapping,-1);
	
	// Create an input component and attach it to the player controller
	UEnhancedInputComponent* EnhancedInputComp =  Cast<UEnhancedInputComponent>(PlayerController->InputComponent) ;
	if (!EnhancedInputComp )
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" EnhancedInputComp  ccast failded "));}
		return;
	}
	
	if(OpenUIAction)
	{
		EnhancedInputComp->BindAction(	OpenUIAction,ETriggerEvent::Triggered,this,&ABaseProceduralActor::ToggleTab);
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" BindAcction done "));}
	}
		
	
	
}

void ABaseProceduralActor::ToggleTab()
{
	if (!IsInGameThread())
	{
		// The game is not running, return or handle the error
		return;
	}
	
	if (ControllerWindow.IsValid() && ControllerWindow->IsVisible())
	{
		// The window is already visible, so just hide it
		ControllerWindow->HideWindow();
		FSlateApplication::Get().DestroyWindowImmediately(ControllerWindow.ToSharedRef());
		ControllerWindow.Reset();
	}
	else
	{
		// Create a new window and keep a reference to it
		if (!ControllerWidget.IsValid())
		{
			ControllerWidget = SNew(SGenerationControllerTab);
			SGenerationControllerTab::GenerateDelegate.BindUObject(this,&ABaseProceduralActor::OnReGenerate);
		}

		ControllerWindow = SNew(SWindow)
			.Title(FText::FromString("Controller"))
			.SizingRule(ESizingRule::UserSized)
			.AutoCenter(EAutoCenter::None)
			.ClientSize(FVector2D(200, 800))
			.IsTopmostWindow(true)
			.CreateTitleBar(true)
			.SupportsMaximize(false)
			.SupportsMinimize(true)
			.HasCloseButton(true)
			.Content()
			[                ControllerWidget.ToSharedRef()            ];

		FSlateApplication::Get().AddWindow(ControllerWindow.ToSharedRef(), true);
	}
/*
	if (ControllerWindow.IsValid())
	{
		if (ControllerWindow->IsVisible())
		{
			ControllerWindow->HideWindow();
		}
		else
		{
			ControllerWindow->ShowWindow();
		}
	}
	else
	{
		ControllerWidget = SNew(SGenerationControllerTab);
		SGenerationControllerTab::GenerateDelegate.BindUObject(this,&ABaseProceduralActor::OnReGenerate);

		ControllerWindow = SNew(SWindow)
			.Title(FText::FromString("Controller"))
			.SizingRule(ESizingRule::UserSized)
			.AutoCenter(EAutoCenter::None)
			.ClientSize(FVector2D(800, 600))
			.IsTopmostWindow(true)
			.CreateTitleBar(true)
			.SupportsMaximize(false)
			.SupportsMinimize(true)
			.HasCloseButton(true)
			.Content()
			[            ControllerWidget.ToSharedRef()        ];

		FSlateApplication::Get().AddWindow(ControllerWindow.ToSharedRef(), true);
	}*/

	
}


void ABaseProceduralActor::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	// Check if the dock tab has been created yet
	if (MyDockTab.IsValid())
	{
		// Update the dock tab's label with the actor's name
		FString ActorName = GetName();
		MyDockTab->SetLabel(FText::FromString(ActorName));
	}
}

bool ABaseProceduralActor::OnReGenerate()
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(-2, 2.0f, FColor::Blue, TEXT(" Generating Actor  "));
	}


	for(int32 j = TotalTileMesh.Num()-1 ; j>= 0 ; j--)
	{
		UTileMesh* TileMesh =TotalTileMesh[j];
		TileMesh->OwnerTileList.Empty();
		TileMesh->InstancedMesh->ClearInstances();
	}

	//
	for (int32 i = AllTilesPTR.Num() - 1; i >= 0; i--)
	{
		UTile* Tile = AllTilesPTR[i];
		Tile->ConditionalBeginDestroy();
		AllTilesPTR.RemoveAt(i);
		RemainingTiles.Remove(Tile);
		CollapsedTiles.Remove(Tile);
		
	}
	AllTilesPTR.Empty();
	RemainingTiles.Empty();
	CollapsedTiles.Empty();

	
	
	//init the class
	//Init();

	//GENERATING TILE
	CalculateMeshLength();
	GenerateTile();
	SetTileLength(Actor_Length_X,Actor_Length_Y);
	GenerateBaseFloor(AllTilesPTR);

	
	
	if (!AllTilesPTR.IsEmpty() && !TotalTileMesh.IsEmpty())
	{
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT(" BOTH TILE AND TOTAL MESH AVAILABLE WAVE FUNCTION CALLING  "));
		}

		// STARTING THE MAIN ALGORITHM
		WaveFunctionCollapse();
	}
	else
	{
		// error occurred, display an error message
		if (GEngine) {
			GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("Could not generate tile or total mesh. Aborting."));
		}
	}
	
	
	

	return true;
}

bool ABaseProceduralActor::Init()
{
	if (GetTileMeshData())
	{
		if (SetTileMeshData())
		{
			//setting the floor mesh
			FlorInstanceMeshComponent->SetStaticMesh(FloorMesh);

			//FOR DEBUG CONTAINER ACTOR
			DebugContainerAcotr = GetWorld()->SpawnActor<ACoreDebugContainer>(FVector::ZeroVector, FRotator::ZeroRotator);

			return true;
		}
	}

	return false;
	
}

bool ABaseProceduralActor::GetTileMeshData()
{
	if( TileMeshDataAsset != nullptr)
	{
		return true ;
	}
	FString AssetPath = FString::Printf(TEXT("ProceduralGeneration/Data/%s.%s"), *TileMeshDataAssetName, *TileMeshDataAssetName);
	TileMeshDataAsset = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *AssetPath));

	// or
	//FName AssetName = FName(*TileMeshDataAssetName);
	//TileMeshDataAsset = Cast<UDataTable>(StaticLoadObject(UDataTable::StaticClass(), nullptr, *TileMeshDataAssetName_FName.ToString()));
	if(TileMeshDataAsset == nullptr)
	{
		return false ;
	}
	if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green, TEXT("  Data asset imported  !!"));}
	return true;
	
}

bool ABaseProceduralActor::SetTileMeshData()
{
	
	TileMeshDataAsset->GetAllRows<FTileMeshData>(TEXT(""), TileMeshDataArray);
	if(TileMeshDataArray.IsEmpty())
	{
		return  false ;
	}
	if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT(" TileMesh Initializing ...."));}
	DefaultTileMesh->Init(this ,TileMeshDataArray[0]);
	InitTileMesh(TotalTileMesh,TileMeshDataArray);
	return true;
	
}

void ABaseProceduralActor::InitTileMesh(TArray<UTileMesh*>& totaltilemeshes, TArray<FTileMeshData*>& totaltilemeshedatas)
{
	for (FTileMeshData* tilemeshdata : totaltilemeshedatas )
	{
		UTileMesh* TileMesh = NewObject<UTileMesh>();
		TileMesh->Init(this,tilemeshdata);
		totaltilemeshes.Add(TileMesh);
			
	}
}

// THE MAIN ALGORITHM
void ABaseProceduralActor::WaveFunctionCollapse()
{

		//Adding RemainingTile To All Tile
		RemainingTiles.Reserve(AllTilesPTR.Num());
		for(UTile* Tile : AllTilesPTR)
			
			{
				RemainingTiles.Add(Tile)  ;
			}
		
	
		// FIRST RANDOM ID FROM STREAM
		Stream.GenerateNewSeed();
		int FirstIndices =  UKismetMathLibrary::RandomIntegerFromStream(RemainingTiles.Num()-1,Stream);
		
		//Pick A Random Tile	//For the first time choose from stream
		UTile* FirstRandomTile = RemainingTiles[6];
		
		// ADDING INSTANCE OF THE SELECTED MESH
		AddInstanceMesh(FirstRandomTile);
		//Update  Collapsed Tile Data
		UpdateCollapsedTileData(FirstRandomTile,AllTilesPTR,RemainingTiles,CollapsedTiles);

		//UPDATE THE SURROUNDING TILES AVAILABLE MESH
		UpdateSurroundingMesh(FirstRandomTile,AllTilesPTR);
	
		while (!RemainingTiles.IsEmpty())
		{
			// CHOOSE A TILE DEPENDING ENTROPY OF THE TILE
			UTile* Tile = ReturnTileWithLowestEntropy(RemainingTiles);
			AddInstanceMesh(Tile);
			UpdateCollapsedTileData(Tile,AllTilesPTR,RemainingTiles,CollapsedTiles);
			UpdateSurroundingMesh(Tile,RemainingTiles);
		}
}

void ABaseProceduralActor::UpdateCollapsedTileData(UTile*Tile , TArray<UTile*>& TotalTilee ,TArray<UTile*>& RemainingTile, TArray<UTile*>& TotalCollapsedTile)
{
	//Update Collapse Status in the main tile

	//FTile&CollapsedTile = TotalTile[ID-1];
	Tile->SetCollapseStatus(EcollapseStatus::Collapsed);

	//Remove From Remaining Title
	RemainingTile.Remove(Tile);

	// Add th the collapsed tile
	TotalCollapsedTile.Add(Tile);
}

UTile*  ABaseProceduralActor::ReturnTileWithLowestEntropy(TArray<UTile*>& TotalTile)
{
	int LowestNumberOfTile =999;
	UTile* Tile = DefaultTile ;
	for(UTile* tile : TotalTile )
	{
		if(tile->AllAvailableMeshToChooseFrom.Num()<LowestNumberOfTile )
		{

			LowestNumberOfTile=tile->AllAvailableMeshToChooseFrom.Num();
			Tile = tile;
			
		}
	}
	return Tile;
}

UTile* ABaseProceduralActor::GetTileByID(int ID, TArray<UTile*>& TotalTile)
{
	for (UTile* Tile : TotalTile)
	{
		if(Tile->ID==ID)
			return  Tile ;
	}
	//return &DefaultTile;
	return nullptr;
}

UTile* ABaseProceduralActor::GetTileByPosition2D(FMatrixPosition Pos, TArray<UTile*>& TotalTile)
{
	int32 index = ((Pos.Y - 1) * Map_Width) + (Pos.X - 1);
	return TotalTile[index];
/*	for (UTile* Tile :TotalTile)
	{
		if(Tile->Position_2D.X == Pos.X && Tile->Position_2D.Y == Pos.Y )
		{
			return Tile;
		}
	}
	//if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("  ERROR IN TILE FOUND RETURN DEFAULT TILE  "));}
	//return &DefaultTile;
	return  nullptr;*/
}

// CALCULATE LENGTH OF THE  FLOOR MESH 
void ABaseProceduralActor::CalculateMeshLength()
{
	if(bWantCustomTileSize == false)
	{
		if(FloorMesh ==nullptr)
		{
			if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Yellow, TEXT("  Tile Size Calculation Failed"));}
			return;
		}
		FVector Center ;
		FVector Extent;
		FloorMesh->GetBoundingBox().GetCenterAndExtents(Center,Extent);
		Actor_Length_X = (Extent.X-Center.X)*2;
		Actor_Length_Y = (Extent.Y-Center.Y)*2;
		Actor_Length_Z = (Extent.Z-Center.Z)*2;
	}
}

//THIS FUNCTION GENERATES TILES 
bool ABaseProceduralActor::GenerateTile()
{
	if (!IsInGameThread())
	{
		// The game is not running, return or handle the error
		return false;
	}
	if(TotalTileMesh.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Total Tile Not set properly Tile Generation Aborted!!!  "));}
	}
	bool GenerationDone= false;
	int id=0;
	for (int Y = 0 ; Y<  Map_Width ; Y++)
	{
		for (int X = 0 ; X< Map_Height ; X++)
		{
			
			id++;
			AllTiles_Float ++ ;
			int Ypos=Y+1;
			int Xpos=X+1;
			FMatrixPosition POS(Xpos,Ypos);
			FVector2D UnscaledLoc = FVector2d(X,Y);
			

			
			// create a new instance of UTile with NewObject
			UTile* Tile = NewObject<UTile>();

			// create a shared pointer to Tile
			UTile* TilePtr(Tile);

			// Call the Init function to initialize the object
			TilePtr->Init(id, POS,UnscaledLoc, TotalTileMesh);

			// Add the shared pointer to the array
			AllTilesPTR.Add(TilePtr);
			
		}
	}
	GenerationDone=true;
	return GenerationDone;
}

void ABaseProceduralActor::SetTileLength(int Length_X ,int Length_Y )
{
	if(AllTilesPTR.IsEmpty())
	{
		return;
	}
	for (UTile * Tile : AllTilesPTR)
	{
		Tile->World_Location=FVector(Tile->World_Location_2D_UnScaled.X * Length_X ,Tile->World_Location_2D_UnScaled.Y * Length_Y , 0.0 );
	}
}

/*
bool ABaseProceduralActor::GenerateTile_V2()
{
	bool GenerationDone= false;
	int id=0;
	FTileContainer*CurrentTileContainer ;
	for (int i = 0 ; i< Map_Height ; i++)
	{
		for (int j = 0 ; j< Map_Width ; j++)
		{
			
			std::unique_ptr<FTile> tile(new FTile);
			id++;
			tile->ID = id ;
			AllTiles_Float ++ ;
			tile->Position_2D.Height=i+1;
			tile->Position_2D.Width=j+1;
			tile->World_Location = FVector (i*Actor_Length_X , j*Actor_Length_Y,0.0f);

			FTileContainer* TileContainer = new FTileContainer;
			TileContainer->Tile=std::move(tile);
			CurrentTileContainer=TileContainer;
			FTileContainer*NextTileCotainer =new FTileContainer;
			CurrentTileContainer->NextTileContainer =NextTileCotainer;
			CurrentTileContainer=NextTileCotainer;

			if(AllTiles_HEAD==nullptr)
			{
				AllTiles_HEAD=new FTileContainer;
				AllTiles_HEAD->Tile=std::move(tile);
				AllTiles_HEAD->NextTileContainer=CurrentTileContainer;
			}
		}
	}
	GenerationDone=true;
	return GenerationDone;
	
}*/

// THIS FUNCTION CHOOSE RANDOM TILE FROM GIVEN ARRAY
UTile* ABaseProceduralActor::ChooseRandomTile(TArray<UTile*>& AllTileToChooseFrom)
{
	
	int RandomTile = FMath::RandRange(0,AllTileToChooseFrom.Num() );
	return AllTilesPTR[RandomTile];
}



void ABaseProceduralActor::GenerateBaseFloor( TArray<UTile*>& TotalTies)
{
	if(!bWantBaseFloor)
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("  want base floor : false "));}
		return;
	}
	if(TotalTies.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, TEXT("  TotalTile Empty Base Floor Generation Aborted "));}
		return;
	}
	if(FlorInstanceMeshComponent)
	{
		for(UTile* Tile : TotalTies)
		{
			FTransform Transform ;
			Transform.SetLocation(Tile->World_Location);
			FlorInstanceMeshComponent->AddInstance(Transform);
		}
	}
}

// THIS FUNCTION UPDATE SURROUNDING MAINLY CALL THOSE 4 FUNCTION
void ABaseProceduralActor::UpdateSurroundingMesh(UTile* SelectedTile, TArray<UTile*>& TotalTile)
{
	FMatrixPosition Position2D = SelectedTile->Position_2D;
	if(Position2D.Y-1 >=1 )
	{
		FMatrixPosition Pos (Position2D.X,Position2D.Y-1);
		UTile* LeftNeighbour  = GetTileByPosition2D(Pos,AllTilesPTR);
		UpdateAvailableMesh_Left(SelectedTile,LeftNeighbour);
	}
	if(Position2D.Y+1 <Map_Width )
	{
		
		FMatrixPosition Pos (Position2D.X,Position2D.Y+1);
		UTile* RightNeighbour  = GetTileByPosition2D(Pos,AllTilesPTR);
		UpdateAvailableMesh_Right(SelectedTile,RightNeighbour);
	}
	if(Position2D.X+1 <Map_Height )
	{
		
		FMatrixPosition Pos (Position2D.X+1,Position2D.Y);
		UTile* UpNeighbour  = GetTileByPosition2D(Pos,AllTilesPTR);
		UpdateAvailableMesh_Up(SelectedTile,UpNeighbour);
	}
	if(Position2D.X-1 >=1 )
	{
		
		FMatrixPosition Pos (Position2D.X-1,Position2D.Y);
		UTile* DownNeighbour  = GetTileByPosition2D(Pos,AllTilesPTR);
		UpdateAvailableMesh_Down(SelectedTile,DownNeighbour);
	}
}

// UPDATE LEFT SIDE OF THE SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Left(UTile* SelectedTile,UTile* LeftNeighbour)
{
	
	TArray<UTileMesh*> UpdatedAvailableTileMesh;

	if( LeftNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	TArray<UTileMesh*>TileMeshPTR = LeftNeighbour->AllAvailableMeshToChooseFrom;
	
	for (UTileMesh* AvailableTileMesh_Left : TileMeshPTR )
	{
		if (AvailableTileMesh_Left == nullptr) {
			continue;
		}

		if (AvailableTileMesh_Left->CompatibleMeshTag_Right.HasTag(SelectedTile->SelectedTiledMesh->MeshTag)) {
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Left);
		}
			
	}
	LeftNeighbour->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
	
}

// UPDATE RIGHT SIDE OF THE SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Right(UTile* SelectedTile,UTile* RightNeighbour)
{
	
	TArray<UTileMesh*> UpdatedAvailableTileMesh;
	
	if(RightNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	TArray<UTileMesh*>TileMeshPTR = RightNeighbour->AllAvailableMeshToChooseFrom;

	for (UTileMesh* AvailableTileMesh_Right : TileMeshPTR )
	{
		if (AvailableTileMesh_Right == nullptr) {
			continue;
		}
		if(AvailableTileMesh_Right->CompatibleMeshTag_Left.HasTag(SelectedTile->SelectedTiledMesh->MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Right);
	}
	RightNeighbour->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
}

// UPDATE UP SIDE OF SELECTED MESH
void ABaseProceduralActor::UpdateAvailableMesh_Up(UTile* SelectedTile,UTile* UpNeighbour)
{
	TArray<UTileMesh*> UpdatedAvailableTileMesh;
	
	if(UpNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
	{
		return;
	}
	TArray<UTileMesh*>TileMeshPTR = UpNeighbour->AllAvailableMeshToChooseFrom;
	for (UTileMesh* AvailableTileMesh_Up : TileMeshPTR )
	{
		if (AvailableTileMesh_Up == nullptr) {
			continue;
		}
		if(AvailableTileMesh_Up->CompatibleMeshTag_Down.HasTag(SelectedTile->SelectedTiledMesh->MeshTag))
			UpdatedAvailableTileMesh.Add(AvailableTileMesh_Up);
	}
	UpNeighbour->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
}

// UPDATE DOWN SIDE OF SELECTED MESH 
void ABaseProceduralActor::UpdateAvailableMesh_Down(UTile* SelectedTile,UTile* DownNeighbour)
{
		TArray<UTileMesh*> UpdatedAvailableTileMesh;
	
		if(DownNeighbour->CollapseStatus==EcollapseStatus::Collapsed)
		{
			return;
		}
		TArray<UTileMesh*>TileMeshPTR = DownNeighbour->AllAvailableMeshToChooseFrom;
		for (UTileMesh* AvailableTileMesh_Down :TileMeshPTR )
		{
			if (AvailableTileMesh_Down == nullptr) {
				continue;
			}
			if(AvailableTileMesh_Down->CompatibleMeshTag_Up.HasTag(SelectedTile->SelectedTiledMesh->MeshTag))
				UpdatedAvailableTileMesh.Add(AvailableTileMesh_Down);
		}
		DownNeighbour->AllAvailableMeshToChooseFrom =UpdatedAvailableTileMesh;
}


// CHOOSE AN RAND0M ARRAY FROM GIVEN ARRAY OF UTile BASED ON ENTROPY
UTileMesh* ABaseProceduralActor::RandomMeshFromAvailableMesh(UTile* Tile)
{
	//if(Tile.AllAvailableMeshToChooseFrom.Num() == 0)
	if(Tile->AllAvailableMeshToChooseFrom.IsEmpty())
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT("   Available mesh list is empty For this tile unable to select any random Mesh "));}
		return DefaultTileMesh;
	}
	
	int RandomMESH = FMath::RandRange(0,Tile->AllAvailableMeshToChooseFrom.Num()-1 );
	UTileMesh* SelectedTileMesh = Tile->AllAvailableMeshToChooseFrom[RandomMESH];
	return SelectedTileMesh;
}

void ABaseProceduralActor::AddInstanceMesh(UTile* SelectedTile )
{
	
	SelectedTile->SelectedTiledMesh = RandomMeshFromAvailableMesh(SelectedTile);
	if(SelectedTile->SelectedTiledMesh->TileMesh ==nullptr  )
	{
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, TEXT(" Instance Add Failedd Selected Tile Didint have any Selected  Mesh "));}
		return;
	}
	//SelectedTile->SelectedTiledMesh.OwnerTileList.Add(SelectedTile);
	if(SelectedTile->SelectedTiledMesh->TileMesh != nullptr)
	{
		FTransform SpawnTransform ;
		SpawnTransform.SetLocation(SelectedTile->World_Location);
		SelectedTile->SelectedTiledMesh->InstancedMesh->AddInstance(SpawnTransform);
		//FlorInstanceMeshComponent->AddInstance(SpawnTransform);
		if(GEngine){GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Green,  TEXT(" INSTANCE ADING DONE "));}
	}
}






