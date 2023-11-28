// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConversationNodeDefinition.h"
#include "BranchingFragment.generated.h"

/**
 * 
 */
UCLASS(Abstract)
class CONVERSATIONSYSTEM_API UBranchingFragment : public UContentFragment
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Branches, meta = (TitleProperty = "DisplayName"), Instanced)
	TArray<TObjectPtr<UTriggerableFragment>> Branches;
};
