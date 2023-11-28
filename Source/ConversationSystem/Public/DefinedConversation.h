// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConversationAsyncAction.h"
#include "DefinedConversation.generated.h"

class UConversationNodeDefinition;

/**
 * 
 */
UCLASS(Blueprintable)
class CONVERSATIONSYSTEM_API UDefinedConversation : public UConversationAsyncAction
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category=Definition)
	TSubclassOf<UConversationNodeDefinition> DefinitionClass;
	
};
