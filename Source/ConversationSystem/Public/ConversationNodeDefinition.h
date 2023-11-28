// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ConversationAsyncAction.h"
#include "ConversationNodeDefinition.generated.h"

struct FReplyOption;

UENUM(BlueprintType)
enum class ECompletionBehavior : uint8
{
	DO_RESTART	UMETA(DisplayName = "Restart"),
	DO_FINISH	UMETA(DisplayName = "Finish"),
	DO_CONTINUE	UMETA(DisplayName = "Continue")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFragmentComplete, ECompletionBehavior, Behavior);

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
	bool FilterFragment(FName InName) {
		return (Trigger.ReplyName == InName);
	}

	UFUNCTION(BlueprintCallable)
	void Complete() {
		OnFragmentComplete.Broadcast(ExpectedBehavior);
	}

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category=ConversationFragment)
	void DoProcess(UConversationAsyncAction* Conversation);
	virtual void DoProcess_Implementation(UConversationAsyncAction* Conversation) {}


public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, Category=Branch)
	FReplyOption Trigger;

	UPROPERTY(EditDefaultsOnly, Category=Branch)
	ECompletionBehavior ExpectedBehavior;

	UPROPERTY(BlueprintAssignable)
	FOnFragmentComplete OnFragmentComplete;
};



UCLASS(Blueprintable, Const, Abstract)
class CONVERSATIONSYSTEM_API UConversationNodeDefinition : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Display)
	FText DisplayName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Branches, Instanced, meta = (TitleProperty = "DisplayName"))
	TArray<TObjectPtr<UConversationNodeFragment>> Fragments;

};
