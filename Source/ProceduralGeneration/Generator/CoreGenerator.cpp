// Do Whatever you  want with this code
#include "CoreGenerator.h"
#include "EditorStyleSet.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "PropertyCustomizationHelpers.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "Widgets/Layout/SScrollBox.h"

#include "ProceduralGeneration/Tiles/Tile.h"

#define LOCTEXT_NAMESPACE "Editor Window"



UCoreGenerator::UCoreGenerator()
{
	TileCount=0;
}

UCoreGenerator::~UCoreGenerator()
{
	
}

void UCoreGenerator::Init(TMap<int32,USpawnable*>*in_SpawnableContainer ,UStaticMesh*InUnitMesh,int InMapHeight , int InMapWidth )
{
	SpawnableContainer=in_SpawnableContainer;
	UnitMesh=InUnitMesh;
	Map_Height=InMapHeight;
	Map_Width=InMapWidth;
}



TArray<UTile*>* UCoreGenerator::Run( )
{
	GenerateTile(TileContainer,SpawnableContainer, TileCount,Map_Height,Map_Width);

	if(CalculateMeshDimension(UnitMesh ,Actor_Length_X,Actor_Length_Y,Actor_Length_Z))
	{
		SetTilesWorldLocation(TileContainer,Actor_Length_X,Actor_Length_Y);
	}

	

	return &TileContainer;
}

bool UCoreGenerator::CalculateMeshDimension(const UStaticMesh*StaticMesh , float& out_LenX ,float&  out_LenY , float&  out_LenZ )
{

	
	if(StaticMesh!=nullptr)
	{
		FVector Center ;
		FVector Extent;
		StaticMesh->GetBoundingBox().GetCenterAndExtents(Center,Extent);
		out_LenX =(Extent.X * 2);
		out_LenY = (Extent.Y * 2);
		out_LenZ = 0;//(Extent.Z-Center.Z)*2;
		return true;
	}
	else
	{
		return false;
	}
}

bool UCoreGenerator::GenerateTile(TArray<UTile*>& in_TileContainer, TMap<int32,USpawnable*>* in_SpawnableContainer,
	int& in_TileCount, int in_Height, int in_Width)
{
	int id=0;
	in_TileCount =  0;
	for (int Y = 0 ; Y<  in_Width ; Y++)
	{
		//int Ypos=Y+1;
		for (int X = 0 ; X< in_Height ; X++)
		{
			
			id++;
			in_TileCount ++ ;
			
			//int Xpos=X+1;
			FVector2D POS(X,Y);
			
			// create a new instance of UTile with NewObject
			UTile* Tile = NewObject<UTile>();

			// create a shared pointer to Tile
			UTile* TilePtr(Tile);

			// Call the Init function to initialize the object
			TilePtr->Init(id, POS, in_SpawnableContainer);

			// Add the shared pointer to the array
			in_TileContainer.Add(TilePtr);
			
		}
	}
	return true;
}

void UCoreGenerator::SetTilesWorldLocation(TArray<UTile*>& in_TileContainer, int Length_X, int Length_Y)
{
	if(in_TileContainer.IsEmpty())
	{
		return;
	}
	for (UTile * Tile : in_TileContainer)
	{
		Tile->GetWorldLocation()=FVector(Tile->GetPosition2D().X * Length_X ,Tile->GetPosition2D().Y * Length_Y , 0.0 );
	}
}

void UCoreGenerator::DrawPositionIndicator(TArray<UTile*>* in_TileContainer)
{

	UWorld* World = GetWorld();  // Get a reference to the current world

	for (UTile* Tile : *in_TileContainer)
	{
		FVector Location = Tile->GetWorldLocation();
		//DrawDebugSphere(World,Location,50,20,FColor::Red,true,-1);
		DrawDebugPoint(World,Location,20,FColor::Green,true,-1,0);//depth priority of 0 means always visible
		DrawDebugString(GetWorld(), Location, *FString::Printf(TEXT("Position: %f,%f"),Tile->GetPosition2D().Y, Tile->GetPosition2D().X), nullptr, FColor::Red, -1.0F, false);
		bDrawn =true;
	}
	
}

void UCoreGenerator::RemoveIndicator(TArray<UTile*>* in_TileContainer)
{
	UWorld* World = GetWorld();  // Get a reference to the current world

		for (UTile* Tile : *in_TileContainer)
		{
			FVector Location = Tile->GetWorldLocation();
			//DrawDebugSphere(World,Location,50,20,FColor::Red,true,-1);
			DrawDebugPoint(World,Location,20,FColor::Green,false,0,0);//depth priority of 0 means always visible
			bDrawn =false;
		}
}

bool UCoreGenerator::OnDebug()
{
	if(bDrawn)
	{
		RemoveIndicator(&TileContainer);
	}
	DrawPositionIndicator(&TileContainer);
	return true;
}

FString UCoreGenerator::GetDataAssetPath() const
{
	return SelectedDataAssetPath;
}
/*
TSharedRef<SWidget> UCoreGenerator::HandleMenuContent()
{
	ScanDataAssets();
	// Create a list view widget to display the available custom data assets
	TSharedPtr<SListView<UObject*>> ListView;
	SAssignNew(ListView, SListView<UObject*>)
		.ListItemsSource(&CustomDataAssetList)
		.OnGenerateRow(this, &UCoreGenerator::HandleCustomDataAssetListRow);

	// Create a scroll box widget to contain the list view
	TSharedPtr<SScrollBox> ScrollBox;
	SAssignNew(ScrollBox, SScrollBox)
		.Orientation(Orient_Vertical)
		.ScrollBarAlwaysVisible(true)
		+ SScrollBox::Slot()
		[
			ListView.ToSharedRef()
		];

	// Create a border widget to contain the scroll box
	TSharedPtr<SBorder> Border;
	SAssignNew(Border, SBorder)
		.Padding(FMargin(5.0f))
		.BorderImage(FEditorStyle::GetBrush("ToolPanel.GroupBorder"))
		[
			ScrollBox.ToSharedRef()
		];

	// Return the border widget as the menu content of the combo button
	return Border.ToSharedRef();
}

TSharedRef<ITableRow> UCoreGenerator::HandleCustomDataAssetListRow(UObject* Item, const TSharedRef<STableViewBase>& OwnerTable)
{
	return SNew(STableRow<UObject*>, OwnerTable)
		.Padding(FMargin(3.0f))
		[
			SNew(STextBlock)
			.Text(FText::FromName(Item->GetFName()))
		];
}

void UCoreGenerator::ScanDataAssets()
{

	// Get a reference to the asset registry module
	FAssetRegistryModule& AssetRegistryModule = FModuleManager::LoadModuleChecked<FAssetRegistryModule>("AssetRegistry");

	// Create a filter that includes only custom data assets
	FARFilter Filter;
	Filter.ClassNames.Add(UDataAsset::StaticClass()->GetFName());

	// Search for all the custom data assets in the project directory
	TArray<FAssetData> AssetData;
	AssetRegistryModule.Get().GetAssets(Filter, AssetData);

	// Add the custom data assets to the CustomDataAssetList array
	for (const FAssetData& Asset : AssetData)
	{
		UObject* Object = Asset.GetAsset();
		if (Object != nullptr)
		{
			CustomDataAssetList.Add(Object);
		}
	}
}*/

#undef  LOCTEXT