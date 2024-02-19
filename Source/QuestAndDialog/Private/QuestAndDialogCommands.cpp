// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestAndDialogCommands.h"

#define LOCTEXT_NAMESPACE "FQuestAndDialogModule"

void FQuestAndDialogCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "QuestAndDialog", "Bring up QuestAndDialog window", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
