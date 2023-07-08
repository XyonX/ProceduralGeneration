// Do Whatever you  want with this code
#include "CoreGenerator.h"
#include "EditorStyleSet.h"
#include "Widgets/Layout/SExpandableArea.h"
#include "PropertyEditorModule.h"
#include "PropertyCustomizationHelpers.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"
#include "Widgets/Layout/SScrollBox.h"
#include "CoreUI/DockTab/GenerationControllerTab.h"

#define LOCTEXT_NAMESPACE "Editor Window"



UCoreGenerator::UCoreGenerator()
{
	TileCount=0;
}

UCoreGenerator::~UCoreGenerator()
{
	TileContainer =nullptr;
}

void UCoreGenerator::Init(TSharedPtr<SGenerationControllerTab> InTab, UStaticMesh*in_UnitMesh , int in_height , int in_width )
{
	Map_Height=in_height;
	Map_Width=in_width;
	ControllerTab=InTab;
	if(UnitMesh==nullptr)
	UnitMesh=in_UnitMesh;
	
}

bool UCoreGenerator::Run(TArray<UTile*>& in_TileContainer,TMap<int32 ,USpawnable*>*in_SpawnableContainer )
{

	GenerateTile(in_TileContainer, in_SpawnableContainer, TileCount,Map_Height,Map_Width);

	CalculateMeshDimension(UnitMesh ,Actor_Length_X,Actor_Length_Y,Actor_Length_Z);

	SetTilesWorldLocation(in_TileContainer,Actor_Length_X,Actor_Length_Y);

	TileContainer =  &in_TileContainer;

	if(in_TileContainer.Num() ==0)
	{
		return false;
	}
	return true;
}

void UCoreGenerator::AddUIEntry()
{
	if(ControllerTab ==nullptr)
	{
		return;
	}
	// Get the vertical box widget
	TSharedPtr<SVerticalBox> VerticalBoxWidget = StaticCastSharedRef<SVerticalBox>(ControllerTab->GetWidget().ToSharedRef());

	if(VerticalBoxWidget==nullptr)
		return;

	// Add a new slot to the vertical box and create a collapsible box widget inside the slot
	VerticalBoxWidget->AddSlot()
					.VAlign(VAlign_Top)
					.HAlign(HAlign_Fill)
	
				[
					SNew(SExpandableArea)
					.BorderBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 0.5f))
					.BodyBorderBackgroundColor(FLinearColor(0.25f, 0.25f, 0.25f, 0.5f))
					.HeaderContent()
					[
							SNew(SBorder)
							.BorderBackgroundColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f))
								[
								  SNew(STextBlock)
								  .Font(FSlateFontInfo(FPaths::EngineContentDir() / TEXT("Slate/Fonts/Roboto-Bold.ttf"), 10))
								  .ColorAndOpacity(FLinearColor::White)
								  .Text(FText::FromString("Generator"))
								]
					]
					.BodyContent()
					[
						SNew(SVerticalBox)
							+ SVerticalBox::Slot()
							.Padding(5.0f)
							
								[
									SNew(STextBlock)
									.Text(FText::FromString("New Area"))
									/*SNew(SComboButton)
									.OnGetMenuContent(this, &UCoreGenerator::HandleMenuContent)
									.ContentPadding(FMargin(2.0f, 2.0f))
									.ButtonContent()
									[
										SNew(STextBlock)
										.Text(LOCTEXT("CustomDataAsset", "Choose Custom Data Asset"))
									]*/
								]
							
					]
			];
}

void UCoreGenerator::CalculateMeshDimension(const UStaticMesh* StaticMesh , int& out_LenX ,int&  out_LenY , int&  out_LenZ )
{
	
	if(StaticMesh!=nullptr)
	{
		FVector Center ;
		FVector Extent;
		StaticMesh->GetBoundingBox().GetCenterAndExtents(Center,Extent);
		//out_LenX = (Extent.X-Center.X)*2;
		//out_LenY = (Extent.Y-Center.Y)*2;
		out_LenX =(Extent.X * 2);
		out_LenY = (Extent.Y * 2);
		out_LenZ = 0;//(Extent.Z-Center.Z)*2;
	}
}

bool UCoreGenerator::GenerateTile(TArray<UTile*>& in_TileContainer, TMap<INT32,USpawnable*>* in_SpawnableContainer,
	int& in_TileCount, int in_Height, int in_Width)
{
	int id=0;
	in_TileCount =  0;
	for (int Y = 0 ; Y<  in_Width ; Y++)
	{
		int Ypos=Y+1;
		for (int X = 0 ; X< in_Height ; X++)
		{
			
			id++;
			in_TileCount ++ ;
			
			int Xpos=X+1;
			FVector2D POS(Xpos,Ypos);
			FVector2D UnscaledLoc = FVector2d(X,Y);
			
			// create a new instance of UTile with NewObject
			UTile* Tile = NewObject<UTile>();

			// create a shared pointer to Tile
			UTile* TilePtr(Tile);

			// Call the Init function to initialize the object
			TilePtr->Init(id, POS,UnscaledLoc, in_SpawnableContainer);

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
		Tile->World_Location=FVector(Tile->World_Location_2D_UnScaled.X * Length_X ,Tile->World_Location_2D_UnScaled.Y * Length_Y , 0.0 );
	}
}
void UCoreGenerator::SetTilesWorldLocation(UTileMap* in_TileContainer, int Length_X ,int Length_Y)
{
/*	for (auto& Pair : in_TileContainer)
	{
		UTile* Tile = Pair.second;
		Tile->World_Location=FVector(Tile->World_Location_2D_UnScaled.X * Length_X ,Tile->World_Location_2D_UnScaled.Y * Length_Y , 0.0 );
	}*/
}

void UCoreGenerator::DrawPositionIndicator(TArray<UTile*>* in_TileContainer)
{

	UWorld* World = GetWorld();  // Get a reference to the current world

	for (UTile* Tile : *in_TileContainer)
	{
		FVector Location = Tile->World_Location;
		//DrawDebugSphere(World,Location,50,20,FColor::Red,true,-1);
		DrawDebugPoint(World,Location,20,FColor::Green,true,-1,0);//depth priority of 0 means always visible
		DrawDebugString(GetWorld(), Location, *FString::Printf(TEXT("Position: %d,%d"),Tile->Position_2D.Y, Tile->Position_2D.X), nullptr, FColor::Red, -1.0F, false);
		bDrawn =true;
	}
	
}

void UCoreGenerator::RemoveIndicator(TArray<UTile*>* in_TileContainer)
{
	UWorld* World = GetWorld();  // Get a reference to the current world

		for (UTile* Tile : *in_TileContainer)
		{
			FVector Location = Tile->World_Location;
			//DrawDebugSphere(World,Location,50,20,FColor::Red,true,-1);
			DrawDebugPoint(World,Location,20,FColor::Green,false,0,0);//depth priority of 0 means always visible
			bDrawn =false;
		}
}

bool UCoreGenerator::OnDebug()
{
	if(bDrawn)
	{
		RemoveIndicator(TileContainer);
	}
	DrawPositionIndicator(TileContainer);
	return true;
}

FString UCoreGenerator::GetDataAssetPath() const
{
	return SelectedDataAssetPath;
}

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
}

#undef  LOCTEXT