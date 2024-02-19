// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "QuestAndDialogStyle.h"

class FQuestAndDialogCommands : public TCommands<FQuestAndDialogCommands>
{
public:

	FQuestAndDialogCommands()
		: TCommands<FQuestAndDialogCommands>(TEXT("QuestAndDialog"), NSLOCTEXT("Contexts", "QuestAndDialog", "QuestAndDialog Plugin"), NAME_None, FQuestAndDialogStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};