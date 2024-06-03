// Fill out your copyright notice in the Description page of Project Settings.


#include "UD2GameInstance.h"
#include "GameFramework/GameUserSettings.h"

void UUD2GameInstance::SetVSyncEnabled(bool bEnable)
{
	if (UGameUserSettings* UserSettings = GEngine->GetGameUserSettings())
	{
		UserSettings->SetVSyncEnabled(bEnable);
		UserSettings->ApplySettings(false);
		UserSettings->SaveSettings();
	}
}
