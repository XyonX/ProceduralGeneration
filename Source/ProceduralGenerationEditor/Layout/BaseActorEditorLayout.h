// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"




class PROCEDURALGENERATIONEDITOR_API FBaseActorEditorLayout
{
public:
	FBaseActorEditorLayout();
	~FBaseActorEditorLayout();

	TSharedRef<FTabManager::FLayout> EditorLayout ();
};
