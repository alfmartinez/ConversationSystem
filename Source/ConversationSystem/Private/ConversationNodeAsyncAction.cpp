// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationNodeAsyncAction.h"
#include "ConversationSubsystem.h"

UConversationNodeAsyncAction* UConversationNodeAsyncAction::DisplayConversationNode(
    const UObject* WorldContext,
    UConversationNode* Node, 
    UConversationReply* Reply
)
{
    UWorld* ContextWorld = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
    if (!ensureAlwaysMsgf(IsValid(WorldContext), TEXT("World Context was not valid.")))
    {
        return nullptr;
    }

    UConversationNodeAsyncAction* NewAction = NewObject<UConversationNodeAsyncAction>();
    NewAction->ContextWorld = ContextWorld;
    NewAction->ConversationNode = Node;
    NewAction->ConversationReply = Reply;
    NewAction->ConversationReply->ContextWorld = ContextWorld;
    NewAction->RegisterWithGameInstance(ContextWorld->GetGameInstance());
    return NewAction;
}

void UConversationNodeAsyncAction::Activate()
{
    if (const UWorld* World = GetWorld())
    {
        UGameInstance* GameInstance = World->GetGameInstance();
        UConversationSubsystem* CS = GameInstance->GetSubsystem<UConversationSubsystem>();
        CS->DisplayConversationNode(ConversationNode);
        ConversationReply->OnReply.AddUObject(this, &UConversationNodeAsyncAction::ProcessReply);
        CS->SendReplyOptions(ConversationReply);
        return;
    }

    // If something failed, we can broadcast OnFail, and then wrap up.
    OnFail.Broadcast();
    Cancel();
}

void UConversationNodeAsyncAction::Cancel()
{
    Super::Cancel();
}

void UConversationNodeAsyncAction::ProcessReply(FName Name)
{
    ReplyName = Name;
    OnReply.Broadcast();
}
