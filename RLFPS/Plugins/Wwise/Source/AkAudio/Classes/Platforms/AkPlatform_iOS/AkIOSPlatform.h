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

#pragma once

#if PLATFORM_IOS && !PLATFORM_TVOS

#include "Platforms/AkPlatformBase.h"
#include "AkIOSInitializationSettings.h"

#define TCHAR_TO_AK(Text) (const ANSICHAR*)(TCHAR_TO_ANSI(Text))

using UAkInitializationSettings = UAkIOSInitializationSettings;

struct AKAUDIO_API FAkIOSPlatform : FAkPlatformBase
{
	static const UAkInitializationSettings* GetInitializationSettings()
	{
		return GetDefault<UAkIOSInitializationSettings>();
	}

	static const FString GetPlatformBasePath()
	{
		return FString("iOS");
	}
};

using FAkPlatform = FAkIOSPlatform;

#endif
