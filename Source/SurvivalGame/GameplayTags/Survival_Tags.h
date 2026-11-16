
#pragma once

#include "CoreMinimal.h"
#include "Runtime/GameplayTags/Public/NativeGameplayTags.h"


namespace Survival_Tags
{
	namespace Resources
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Wood);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Stone);
	}
	
	namespace Tools
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Axe);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Pickaxe);
	}
	
	namespace Food
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Banana);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Meat);
	}
	
	namespace Construction
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Floor);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Wall);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Door);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Window);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Bed);
	}
}
