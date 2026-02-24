// Copyright Epic Games, Inc. All Rights Reserved.

#include "RemoveSourceBPLibrary.h"
#include "RemoveSource.h"
#include "Animation/AnimSequence.h"
#include "EditorFramework/AssetImportData.h"

URemoveSourceBPLibrary::URemoveSourceBPLibrary(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

float URemoveSourceBPLibrary::RemoveSourceSampleFunction(float Param)
{
	return -1;
}

void URemoveSourceBPLibrary::SetAnimSequenceSourceFile(UAnimSequence* AnimSequence, const FString& NewSourcePath)
{
    if (!AnimSequence || !AnimSequence->AssetImportData) return;

    UAssetImportData* ImportData = AnimSequence->AssetImportData;

    // Очищаем старые файлы
    ImportData->SourceData.SourceFiles.Empty();

    if (!NewSourcePath.IsEmpty())
    {
        // Добавляем новый файл через правильный API
        // Параметры: (InPath, Index = -1 (добавить в конец), SourceFileLabel)
        ImportData->ScriptedAddFilename(NewSourcePath, -1, FString());
    }

    AnimSequence->MarkPackageDirty();
}