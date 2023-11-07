// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConversationReply.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnConversationReply, FName);

/**
 * 
 */
UCLASS(Blueprintable)
class CONVERSATIONSYSTEM_API UConversationReply : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent, Category = ConversationNode)
	void DisplayOptions();

	UFUNCTION(BlueprintCallable, Category = ConversationNode)
	void DoReply(FName ReplyName) {
		OnReply.Broadcast(ReplyName);
	}

	virtual UWorld* GetWorld() const override
	{
		return ContextWorld.IsValid() ? ContextWorld.Get() : nullptr;
	}

public:
	TWeakObjectPtr<UWorld> ContextWorld = nullptr;

public:
	FOnConversationReply OnReply;
};
