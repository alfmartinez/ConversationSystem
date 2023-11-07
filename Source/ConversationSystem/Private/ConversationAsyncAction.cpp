// Fill out your copyright notice in the Description page of Project Settings.


#include "ConversationAsyncAction.h"

UConversationAsyncAction* UConversationAsyncAction::StartConversation(const UObject* WorldContext, UObject* Outer, TSubclassOf<UConversationAsyncAction> ConversationClass)
{
    UWorld* ContextWorld = GEngine->GetWorldFromContextObject(WorldContext, EGetWorldErrorMode::ReturnNull);
    if (!ensureAlwaysMsgf(IsValid(WorldContext), TEXT("World Context was not valid.")))
    {
        return nullptr;
    }

    UConversationAsyncAction* NewAction = NewObject<UConversationAsyncAction>(Outer, ConversationClass);
    NewAction->ContextWorld = ContextWorld;
    NewAction->RegisterWithGameInstance(ContextWorld->GetGameInstance());
    return NewAction;
}

void UConversationAsyncAction::Activate()
{
    Prepare();
    Start();
}

void UConversationAsyncAction::Cancel()
{
    Super::Cancel();
}

void UConversationAsyncAction::Prepare_Implementation()
{
}

void UConversationAsyncAction::Start_Implementation()
{
    OnStarted.Broadcast();
}

void UConversationAsyncAction::Abort_Implementation()
{
    OnAborted.Broadcast();
    Cancel();
}

void UConversationAsyncAction::Finish_Implementation()
{
    OnFinished.Broadcast();
    Cancel();
}
