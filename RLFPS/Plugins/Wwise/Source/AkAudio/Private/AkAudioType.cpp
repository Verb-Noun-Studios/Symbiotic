/*******************************************************************************
The content of the files in this repository include portions of the
AUDIOKINETIC Wwise Technology released in source code form as part of the SDK
package.

Commercial License Usage

Licensees holding valid commercial licenses to the AUDIOKINETIC Wwise Technology
may use these files in accordance with the end user license agreement provided
with the software or, alternatively, in accordance with the terms contained in a
written agreement between you and Audiokinetic Inc.

Copyright (c) 2021 Audiokinetic Inc.
*******************************************************************************/

#include "AkAudioType.h"

#include "Async/Async.h"
#include "AkAudioModule.h"
#include "AkAudioDevice.h"
#include "AkGroupValue.h"
#include "AkFolder.h"
#include "Core/Public/Modules/ModuleManager.h"

void UAkAudioType::PostLoad()
{
	Super::PostLoad();
	if (HasAnyFlags(RF_ClassDefaultObject))
	{
		return;
	}
	
	if (FModuleManager::Get().IsModuleLoaded(IAkAudioModule::GetAkAudioModuleName()))
	{
		Load();
	}
	else
	{
		FAkAudioDevice::DelayAssetLoad(this);
	}
}

void UAkAudioType::MarkDirtyInGameThread()
{
#if WITH_EDITOR
	AsyncTask(ENamedThreads::GameThread, [this] 
		{
			MarkPackageDirty();
		});
#endif
}

bool UAkAudioType::ShortIdMatchesName(AkUInt32& OutIdFromName)
{
	if (auto AudioDevice = FAkAudioDevice::Get())
	{
		if (IsA<UAkGroupValue>())
		{
			FString ValueName;
			GetName().Split(TEXT("-"), nullptr, &ValueName);
			OutIdFromName = AudioDevice->GetIDFromString(ValueName);
		}
		else
		{
			OutIdFromName = AudioDevice->GetIDFromString(GetName());
		}

		if (ShortID != OutIdFromName)
		{
			//Folder asset name does not correspond to actual wwise object name and we don't use the short ID anyway
			if (IsA<UAkFolder>())
			{
				return true;
			}
			if (ShortID != 0) 
			{
				UE_LOG(LogAkAudio, Warning, TEXT("%s - Current Short ID '%u' is different from expected ID '%u'"), *GetName(), ShortID, OutIdFromName);
			}
			return false;
		}
	}
	return true;
}

void UAkAudioType::Load()
{
	ValidateShortId(false);
}

void UAkAudioType::ValidateShortId(bool bMarkAsDirty)
{
	AkUInt32 IdFromName;
	if (!ShortIdMatchesName(IdFromName))
	{
		UE_LOG(LogAkAudio, Log, TEXT("%s - Updating Short ID from '%u' to '%u'"), *GetName(), ShortID, IdFromName);

		ShortID = IdFromName;
		if (bMarkAsDirty)
		{
			MarkDirtyInGameThread();
		}
	}
}

#if WITH_EDITOR
void UAkAudioType::Reset()
{
	if (ShortID != 0)
	{
		ShortID = 0;
		bChangedDuringReset = true;
	}

	if (bChangedDuringReset)
	{
		bChangedDuringReset = false;
		MarkDirtyInGameThread();
	}
}
#endif
