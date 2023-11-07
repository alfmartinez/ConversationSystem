// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConversationNode.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class CONVERSATIONSYSTEM_API UConversationNode : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = ConversationNode)
	void Display();
};
