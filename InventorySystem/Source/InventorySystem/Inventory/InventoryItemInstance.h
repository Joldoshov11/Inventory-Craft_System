// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "InventorySystem/Core/Gameplay/GameplayTagStack.h"
#include "Templates/SubclassOf.h"

#include "InventoryItemInstance.generated.h"

class FLifetimeProperty;

class UInventoryItemDefinition;
class UInventoryItemFragment;
struct FFrame;
struct FGameplayTag;

/**
 * ULyraInventoryItemInstance
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnStackChange);

UCLASS(BlueprintType)
class UInventoryItemInstance : public UObject
{
	GENERATED_BODY()

public:
	UInventoryItemInstance(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	//~UObject interface
	virtual bool IsSupportedForNetworking() const override { return true; }
	//~End of UObject interface

	// Adds a specified number of stacks to the tag (does nothing if StackCount is below 1)
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category=Inventory)
	void AddStatTagStack(FGameplayTag Tag, int32 StackCount);

	// Removes a specified number of stacks from the tag (does nothing if StackCount is below 1)
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category= Inventory)
	void RemoveStatTagStack(FGameplayTag Tag, int32 StackCount);

	// Returns the stack count of the specified tag (or 0 if the tag is not present)
	UFUNCTION(BlueprintCallable, Category=Inventory)
	int32 GetStatTagStackCount(FGameplayTag Tag) const;

	UFUNCTION(BlueprintCallable, Category=Inventory)
	int GetItemStack();

	UFUNCTION(BlueprintCallable, Category=Inventory)
	void SetItemStack(int32 InStack);

	UPROPERTY(BlueprintAssignable)
	FOnStackChange OnStackChange;

	UPROPERTY(BlueprintAssignable)
	FOnStackChange OnItemRemove;
	
	UPROPERTY(BlueprintReadWrite,Category = "Inventory")
	int32 ItemStack;

	
	// Returns true if there is at least one stack of the specified tag
	UFUNCTION(BlueprintCallable, Category=Inventory)
	bool HasStatTag(FGameplayTag Tag) const;

	TSubclassOf<UInventoryItemDefinition> GetItemDef() const
	{
		return ItemDef;
	}

	UFUNCTION(BlueprintCallable, BlueprintPure=false, meta=(DeterminesOutputType=FragmentClass),Category = "Inventory")
	const UInventoryItemFragment* FindFragmentByClass(TSubclassOf<UInventoryItemFragment> FragmentClass) const;

	template <typename ResultClass>
	const ResultClass* FindFragmentByClass() const
	{
		return (ResultClass*)FindFragmentByClass(ResultClass::StaticClass());
	}
	
	UPROPERTY(BlueprintReadWrite, Replicated,Category = "Inventory")
	TSubclassOf<UInventoryItemDefinition> ItemDef;
	
	void SetItemDef(TSubclassOf<UInventoryItemDefinition> InDef);
private:
#if UE_WITH_IRIS
	/** Register all replication fragments */
	
#endif // UE_WITH_IRIS


	friend struct FInventoryList;

private:
	UPROPERTY(Replicated)
	FGameplayTagStackContainer StatTags;

	// The item definition

};
