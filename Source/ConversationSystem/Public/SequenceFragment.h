// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ConversationNodeDefinition.h"
#include "ConversationAsyncAction.h"
#include "SequenceFragment.generated.h"

/**
 * 
 */
UCLASS()
class CONVERSATIONSYSTEM_API USequenceFragment : public UTriggerableFragment
{
	GENERATED_BODY()
	
public:
	virtual void DoProcess_Implementation(UConversationAsyncAction* Conversation) override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Sequence, Instanced, meta = (TitleProperty = "DisplayName"))
	TArray<TObjectPtr<UConversationNodeFragment>> Fragments;
private:
	void ProcessFragment();

	UFUNCTION()
	void Advance(ECompletionBehavior InBehavior);

	int Index;
	UConversationAsyncAction* Conversation;
	TWeakObjectPtr<UConversationNodeFragment> CurrentFragment;
};


UCLASS()
class CONVERSATIONSYSTEM_API USequenceContentFragment : public UContentFragment
{
	GENERATED_BODY()

public:
	virtual void DoProcess_Implementation(UConversationAsyncAction* Conversation) override;
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Sequence, Instanced, meta = (TitleProperty = "DisplayName"))
	TArray<TObjectPtr<UContentFragment>> Fragments;
private:
	void ProcessFragment();

	UFUNCTION()
	void Advance(ECompletionBehavior InBehavior);

	int Index;
	UConversationAsyncAction* Conversation;
	TWeakObjectPtr<UConversationNodeFragment> CurrentFragment;
};
