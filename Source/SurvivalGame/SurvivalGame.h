// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/** Main log category used across the project */
DECLARE_LOG_CATEGORY_EXTERN(LogSurvivalGame, Log, All);
inline void ScreenLog(const FString& Message, FColor Color = FColor::Green, float Time = 3.f, int32 Key = -1)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(Key, Time, Color, Message);
	}
}