// Copyright Epic Games, Inc. All Rights Reserved.

#include "QuestAndDialog.h"
#include "QuestAndDialogStyle.h"
#include "QuestAndDialogCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "ToolMenus.h"

static const FName QuestAndDialogTabName("QuestAndDialog");

#define LOCTEXT_NAMESPACE "FQuestAndDialogModule"

void FQuestAndDialogModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FQuestAndDialogStyle::Initialize();
	FQuestAndDialogStyle::ReloadTextures();

	FQuestAndDialogCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FQuestAndDialogCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FQuestAndDialogModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FQuestAndDialogModule::RegisterMenus));
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(QuestAndDialogTabName, FOnSpawnTab::CreateRaw(this, &FQuestAndDialogModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FQuestAndDialogTabTitle", "QuestAndDialog"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FQuestAndDialogModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FQuestAndDialogStyle::Shutdown();

	FQuestAndDialogCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(QuestAndDialogTabName);
}

TSharedRef<SDockTab> FQuestAndDialogModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FQuestAndDialogModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("QuestAndDialog.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FQuestAndDialogModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->TryInvokeTab(QuestAndDialogTabName);
}

void FQuestAndDialogModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FQuestAndDialogCommands::Get().OpenPluginWindow, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("Settings");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FQuestAndDialogCommands::Get().OpenPluginWindow));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FQuestAndDialogModule, QuestAndDialog)