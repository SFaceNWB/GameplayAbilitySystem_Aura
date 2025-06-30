// SFaceNWB Game


#include "AbilitySystem/Data/LootTiers.h"

TArray<FlootItem> ULootTiers::GetLootItems()
{
	TArray<FlootItem> ReturnItems;

	for (FlootItem& Item : LootItems)
	{
		for (int32 i = 0; i < Item.MaxNumberToSpawn; ++i)
		{
			if (FMath::FRandRange(1.0f, 100.0f) < Item.ChanceToSpawn)
			{
				FlootItem NewItem;
				NewItem.LootClass = Item.LootClass;
				NewItem.bLootLevelOverride = Item.bLootLevelOverride;
				ReturnItems.Add(NewItem);
			}
		}
	}

	return  ReturnItems;
}
