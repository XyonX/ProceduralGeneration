// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "CorePlugin/Data/MeshData.h"
#include "CorePlugin/Helpers/DelegateHelper.h"
#include"GameFramework/PlayerController.h"
#include "ProceduralGeneration/Game/TopDownGameInstance.h"
#include "ProceduralGeneration/Pawn/TopDownPawn.h"
#include "TopDownPlayerController.generated.h"

UCLASS()
class PROCEDURALGENERATION_API ATopDownPlayerController  : public APlayerController
{
	GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

	ATopDownPlayerController ();

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	FVector CursorWorldPosition ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	FVector CursorWorldDirection;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	bool bCanPan ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	int CursorRange;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	UStaticMesh*CubeMesh ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Test")
	TSubclassOf<AActor>TesTActor;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Controller")
	ATopDownPawn*TopDownPawn;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Controller")
	FHitResult HitResult;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Controller")
	FVector CursorWorldHitLocation;
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Controller")
	bool bIsCursorPointing;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	float SpawnOffset_Cursor;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	float SpawnOffset_Tile;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	FVector SnappingExtents;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Data")
	UMeshData*MeshData;
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category="Data")
	UTileData*HitTile;
	bool bShouldDrag;
	bool bShouldDrag_Card;
	bool bIsDragSucessfull;
	bool IsLMBPressed ;
	bool IsLMBReleased ;
	bool bIsSnappingTargetAvailable;
	UPROPERTY()
	ASpawnableActor*CursorActor;
	UPROPERTY(EditAnywhere)
	TArray<ASpawnableActor*>PlacedActor;
	bool bIsObjectPlaced ;

	ATopDownPawn* GetTopDownPawn ();
	void OnMouseMoveX (const FInputActionValue& Value);
	void OnMouseMoveXAxis (float Value);
	void OnMouseMoveY (const FInputActionValue& Value);
	void OnMouseMoveYAxis (float Value);
	void OnMouseLMBHold (const FInputActionValue& Value);
	void OnMouseLMBReleased (const FInputActionValue& Value);
	void OnMouseRMBHold (const FInputActionValue& Value);
	void OnMouseRMBReleased (const FInputActionValue& Value);
	void PanHorizontal (float Axis);
	void PanVertical (float Axis);


	//Triangle Intersection Test
	bool TirangleIntersectionTest (TArray<FVector>Triangle_1 ,TArray<FVector>Triangle_2);
	bool BoxIntersectionTest ( FVector Direction , TArray<FVector>Verts);

	void TraceInstanceInBound (ASpawnableActor*SelectedActor, FVector CenterPoint, TArray<int32>& OutOverlappingIndices);
	int32 CalculateClosestInstance ( ASpawnableActor*SelectedActor , FVector HitLocation, TArray<int32>& OutOverlappingIndices) ;
	FVector CalculateSnappingPoints (ASpawnableActor*SelectedActor,int32 TargetIndex , FVector HitLocation);

	
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	float HorizontalPanAcc ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite,Category="Controller")
	float VerticalPanAcc ;
	

	

	UFUNCTION(BlueprintCallable)
	void OnMouseMove(const FVector2D& MousePosition);
	UFUNCTION(BlueprintCallable)
	void SpawnActorAtCursor ();
	bool MouseTrace ();
	UFUNCTION()
	void CursorMovementReceiver(FVector Value);

	UFUNCTION()
	void OnCardDragReceiver_Down (USpawnable*inSpawnable);
	UFUNCTION()
	void OnCardDragReceiver(FVector2D CursorPos);
	UFUNCTION()
	void OnCardDragReceiver_Up ();

	
	
	bool bShowCursor ;
	int32 CurrentCursorActorID;
	int32 HitInstanceIndex;
	TArray<int32> OverlappingInstancesIndices;
	UPROPERTY()
	UInstancedStaticMeshComponent*CurrentSpawnableComponent;
	USpawnable*CurrentSpawnable;
	UPROPERTY()
	ASpawnableActor*CurrentSpawnableActor;
	UPROPERTY()
	UTopDownGameInstance*TopDownGameInstance;
	
	

	UObject*SelectedObject;

	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* MouseX ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* MouseY ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* MouseLMB ;
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Input Actions")
	class UInputAction* MouseRMB ;

	void OnActorDrag(UStaticMesh*Mesh);
	
	
};
