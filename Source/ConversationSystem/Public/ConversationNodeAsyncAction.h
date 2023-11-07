// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/CancellableAsyncAction.h"
#include "ConversationNode.h"
#include "ConversationReply.h"
#include "ConversationNodeAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FConversationNodeDelegate);

/**
 * 
 */
UCLASS()
class CONVERSATIONSYSTEM_API UConversationNodeAsyncAction : public UCancellableAsyncAction
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, DisplayName="Play Conversation Node and Wait for Reply", meta=(WorldContext="WorldContext", BlueprintInternalUseOnly = "true"))
	static UConversationNodeAsyncAction* DisplayConversationNode(const UObject* WorldContext, UConversationNode* Node, UConversationReply* Reply);

    // Start UCancellableAsyncAction Functions
    virtual void Activate() override;
    virtual void Cancel() override;
    // End UCancellableAsyncAction Functions

    // Start UObject Functions
    virtual UWorld* GetWorld() const override
    {
        return ContextWorld.IsValid() ? ContextWorld.Get() : nullptr;
    }
    // End UObject Functions

    UFUNCTION(BlueprintCallable, Category = ConversationReply)
    FName GetReplyName() {
        return ReplyName;
    }

private:
    void ProcessReply(FName Name);

private:
    /** The context world of this action. */
    TWeakObjectPtr<UWorld> ContextWorld = nullptr;

    UConversationNode* ConversationNode = nullptr;

    UConversationReply* ConversationReply = nullptr;

    FName ReplyName;

public:
    UPROPERTY(BlueprintAssignable)
    FConversationNodeDelegate OnFail;

    UPROPERTY(BlueprintAssignable)
    FConversationNodeDelegate OnReply;
};
