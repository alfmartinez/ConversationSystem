// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/CancellableAsyncAction.h"
#include "ConversationAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnConversationDelegate);

/**
 * 
 */
UCLASS(Blueprintable)
class CONVERSATIONSYSTEM_API UConversationAsyncAction : public UCancellableAsyncAction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, DisplayName = "Start Conversation", meta = (WorldContext = "WorldContext", BlueprintInternalUseOnly = "true"))
	static UConversationAsyncAction* StartConversation(const UObject* WorldContext, UObject* Outer, TSubclassOf<UConversationAsyncAction> ConversationClass, FName Name);


	// Start UCancellableAsyncAction Functions
	virtual void Activate() override;
	virtual void Cancel() override;
	// End UCancellableAsyncAction Functions

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Conversation)
	void Prepare();
	void Prepare_Implementation();


	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Conversation)
	void Start();
	void Start_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Conversation)
	void Abort();
	void Abort_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Conversation)
	void Finish(bool bSubconversation = false);
	void Finish_Implementation(bool bSubconversation = false);

	// Start UObject Functions
	virtual UWorld* GetWorld() const override
	{
		return ContextWorld.IsValid() ? ContextWorld.Get() : nullptr;
	}
	// End UObject Functions
private:
	/** The context world of this action. */
	TWeakObjectPtr<UWorld> ContextWorld = nullptr;

	
	
public:

	UPROPERTY(BlueprintReadOnly, Category = Conversation)
	FName ConversationName;

	UPROPERTY(BlueprintAssignable)
	FOnConversationDelegate OnStarted;

	UPROPERTY(BlueprintAssignable)
	FOnConversationDelegate OnFinished;

	UPROPERTY(BlueprintAssignable)
	FOnConversationDelegate OnAborted;

};
