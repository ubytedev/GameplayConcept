//

#include "INativeGameplayConceptConfig.h"
#include "GameplayTagsSettings.h"

IMPLEMENT_MODULE(FDefaultModuleImpl, GameplayConceptRuntime);

void INativeGameplayConceptConfig::CacheRelevantCategoryRemaps()
{
	TArray<FGameplayTagCategoryRemap> Result;
	if (const UGameplayTagsSettings* GTSettings = GetDefault<UGameplayTagsSettings>())
	{
		const TArray<FString> AllRelevantBaseCategories = GetAllRelevantBaseCategories();

		for (const FGameplayTagCategoryRemap& ExistingRemap : GTSettings->CategoryRemapping)
		{
			if (AllRelevantBaseCategories.Contains(ExistingRemap.BaseCategory))
			{
				Result.Add(ExistingRemap);
			}
		}
	}

	UpdateRelevantCategoryRemapsDisplay(Result);
}

void INativeGameplayConceptConfig::AddRelevantBaseCategories() const
{
	UGameplayTagsSettings* GTSettings = GetMutableDefault<UGameplayTagsSettings>();
	if (!GTSettings)
	{
		return;
	}
	
	TArray<FString> AllRelevantBaseCategories = GetAllRelevantBaseCategories();

	// Empty out AllRelevantBaseCategories so we avoid duplicate BaseCategory entries
	for (FGameplayTagCategoryRemap& ExistingRemap : GTSettings->CategoryRemapping)
	{
		const int32 Index = AllRelevantBaseCategories.Find(ExistingRemap.BaseCategory);
		if (Index != INDEX_NONE)
		{
			AllRelevantBaseCategories.RemoveAtSwap(Index, 1, false);
		}
	}

	// Add all unique base categories to GameplayTagSettings
	for (const FString& BaseCategory : AllRelevantBaseCategories)
	{
		FGameplayTagCategoryRemap Remap;
		Remap.BaseCategory = BaseCategory;
		GTSettings->CategoryRemapping.Add(MoveTemp(Remap));
	}
}
