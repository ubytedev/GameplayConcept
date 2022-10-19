//

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagsSettings.h"
#include "INativeGameplayConceptConfig.h"

struct FGameplayTagCategoryRemap;

class GAMEPLAYCONCEPTEDITOR_API INativeGameplayConcept
{
public:
	INativeGameplayConcept() = default;
	virtual ~INativeGameplayConcept() {}
	
	// Helper function to generate all category remaps this gameplay concept wants
	virtual TArray<FGameplayTagCategoryRemap> GenerateDesiredCategoryRemaps() = 0;

	// Get the default mutable config this gameplay concept writes to
	virtual TObjectPtr<INativeGameplayConceptConfig> GetGameplayConceptConfig() = 0;
	
protected:
	/** Apply this gameplay concept */
	virtual bool ApplyGameplayConcept()
	{
		UGameplayTagsSettings* GTSettings = GetMutableDefault<UGameplayTagsSettings>();
		if (!GTSettings)
		{
			return false;
		}

		// Cache the desired category remaps we'll append to GameplayTagsSettings
		const TArray<FGameplayTagCategoryRemap> DesiredCategoryRemaps = GenerateDesiredCategoryRemaps();
	
		for (FGameplayTagCategoryRemap& ExistingRemap : GTSettings->CategoryRemapping)
		{
			for (const FGameplayTagCategoryRemap& DesiredRemap : DesiredCategoryRemaps)
			{
				if (ExistingRemap.BaseCategory == DesiredRemap.BaseCategory)
				{
					for (const FString& Category : DesiredRemap.RemapCategories)
					{
						ExistingRemap.RemapCategories.AddUnique(Category);
					}
				}
			}
		}

		// Update the config, which might display our newly added categories.
		GetGameplayConceptConfig()->CacheRelevantCategoryRemaps();
	
		return true;
	}

	virtual bool RemoveGameplayConcept()
	{
		UGameplayTagsSettings* GTSettings = GetMutableDefault<UGameplayTagsSettings>();
		if (!GTSettings)
		{
			return false;
		}

		// Cache the desired category remaps we'll append to GameplayTagsSettings
		const TArray<FGameplayTagCategoryRemap> DesiredCategoryRemaps = GenerateDesiredCategoryRemaps();
	
		for (FGameplayTagCategoryRemap& ExistingRemap : GTSettings->CategoryRemapping)
		{
			for (const FGameplayTagCategoryRemap& DesiredRemap : DesiredCategoryRemaps)
			{
				if (ExistingRemap.BaseCategory == DesiredRemap.BaseCategory)
				{
					for (const FString& Category : DesiredRemap.RemapCategories)
					{
						ExistingRemap.RemapCategories.Remove(Category);
					}
				}
			}
		}

		// Update the config, which might display our newly added categories.
		GetGameplayConceptConfig()->CacheRelevantCategoryRemaps();
	
		return true;
	}
};
