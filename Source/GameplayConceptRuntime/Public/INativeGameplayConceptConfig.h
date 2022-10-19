//

#pragma once

#include "CoreMinimal.h"
#include "INativeGameplayConceptConfig.generated.h"

struct FGameplayTagCategoryRemap;

UINTERFACE(Meta = (CannotImplementInterfaceInBlueprint))
class UNativeGameplayConceptConfig : public UInterface
{
	GENERATED_BODY()
};

// Minimum functionality for config objects that house config properties related to a GameplayConcept
class GAMEPLAYCONCEPTRUNTIME_API INativeGameplayConceptConfig
{
	GENERATED_BODY()
	
public:
	/** Get all relevant Base remap categories */
	virtual TArray<FString> GetAllRelevantBaseCategories() const = 0;

	// Ideally invoked at UObject::PostInitProperties
	FORCEINLINE void UpdateGameplayConceptConfig()
	{
		AddRelevantBaseCategories();
		CacheRelevantCategoryRemaps();
	}

	// Cache all relevant category remaps
	virtual void CacheRelevantCategoryRemaps();
	
protected:
	// Update your personal display of all relevant category remaps.
	virtual void UpdateRelevantCategoryRemapsDisplay(const TArray<FGameplayTagCategoryRemap>& Remaps) = 0;

private:
	/** Add all base categories this GameplayConcept is using to the default GameplayTagsSettings instance */
	virtual void AddRelevantBaseCategories() const;
};

