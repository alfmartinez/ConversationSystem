// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/CancellableAsyncAction.h"
#include "GameplayTagContainer.h"
#include "ConversationAsyncAction.generated.h"

/** Please add a struct description */
USTRUCT(BlueprintType)
struct FReplyOption
{
	GENERATED_BODY()

public:
	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "ReplyName", MakeStructureDefaultValue = "None"))
	FName ReplyName;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Text"))
	FText Text;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (MultiLine = "true", DisplayName = "LongText"))
	FText LongText;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Query"))
	FGameplayTagQuery Query;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "IsDefault", MakeStructureDefaultValue = "False"))
	bool IsDefault;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "Enabled", MakeStructureDefaultValue = "True"))
	bool Enabled;

	/** Please add a variable description */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (DisplayName = "IsLong", MakeStructureDefaultValue = "True"))
	bool IsLong;
};




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
	UFUNCTION(BlueprintCallable, Category=Conversation)
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

	UPROPERTY(BlueprintReadWrite, Category = DialogueLine)
	int DialogueLineIndex;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Speaker)
	FText Speaker;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Speaker)
	TObjectPtr<UTexture2D> SpeakerImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = Replies, AdvancedDisplay)
	TArray<FReplyOption> ReplyOptions;

	UPROPERTY(BlueprintAssignable)
	FOnConversationDelegate OnStarted;

	UPROPERTY(BlueprintAssignable)
	FOnConversationDelegate OnFinished;

	UPROPERTY(BlueprintAssignable)
	FOnConversationDelegate OnAborted;


};
