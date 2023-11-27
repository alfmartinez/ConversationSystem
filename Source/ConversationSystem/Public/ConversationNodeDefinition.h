// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConversationAsyncAction.h"
#include "ConversationNodeDefinition.generated.h"

struct FReplyOption;

UCLASS(Blueprintable, DefaultToInstanced, EditInlineNew, Abstract)
class CONVERSATIONSYSTEM_API UConversationNodeFragment : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category=ConversationFragment)
	FReplyOption GetTrigger() {
		return Trigger;
	}

	UFUNCTION(BlueprintCallable, Category=ConversationFragment)
	void ProcessFragment(FName InName, UConversationAsyncAction* Conversation ) {
		if (Trigger.ReplyName == InName)
		{
			DoProcess(Conversation);
		}
	}

	UFUNCTION(BlueprintImplementableEvent, Category=ConversationFragment)
	void DoProcess(UConversationAsyncAction* Conversation);

	UPROPERTY(EditDefaultsOnly, Category=Branch)
	FReplyOption Trigger;
};



UCLASS(Blueprintable, Const, Abstract)
class CONVERSATIONSYSTEM_API UConversationNodeDefinition : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Branches, Instanced)
	TArray<TObjectPtr<UConversationNodeFragment>> Fragments;

};
