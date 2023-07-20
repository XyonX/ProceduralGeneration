// MyMeshGenerationWorker.h
#pragma once

#include "CoreMinimal.h"
#include "ProceduralGeneration/Generator/CoreGenerator.h"
#include "GridGenerationWorker.generated.h"

UCLASS()
class PROCEDURALGENERATION_API UGridGenerationWorker : public UObject, public FRunnable
{
	GENERATED_BODY()

public:
	UGridGenerationWorker();

	// Override FRunnable interface
	virtual bool Init() override;
	virtual uint32 Run() override;
	virtual void Stop() override;
	virtual void Exit() override;

	void SetParameters(UCoreGenerator* InGenerator);

private:

	void GenerateMeshSections();


	UPROPERTY()
	UCoreGenerator*Generator;

};


