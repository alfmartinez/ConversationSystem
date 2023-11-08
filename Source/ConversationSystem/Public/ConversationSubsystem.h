// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ConversationReply.h"
#include "ConversationSubsystem.generated.h"

UENUM(BlueprintType)
enum class EConversationStatus : uint8
{
	STARTED			UMETA(DisplayName = "Started"),
	COMPLETED		UMETA(DisplayName = "Completed"),
	ABORTED			UMETA(DisplayName = "Aborted")
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnConversationStatusUpdated, EConversationStatus, Status, FName, Name);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReplyOptionsReceived, UConversationReply*, Options);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNodeDisplay, UConversationNode*, Node);

/**
 * 
 */
UCLASS()
class CONVERSATIONSYSTEM_API UConversationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = ConversationSystem)
	void StartConversation(FName Name) {
		OnConversationStatusUpdated.Broadcast(EConversationStatus::STARTED, Name);
	}

	UFUNCTION(BlueprintCallable, Category = ConversationSystem)
	void FinishConversation(FName Name) {
		OnConversationStatusUpdated.Broadcast(EConversationStatus::COMPLETED, Name);
	}

	UFUNCTION(BlueprintCallable, Category = ConversationSystem)
	void AbortConversation(FName Name) {
		OnConversationStatusUpdated.Broadcast(EConversationStatus::ABORTED, Name);
	}

	UFUNCTION(BlueprintCallable, Category = ConversationSystem)
	void DisplayConversationNode(UConversationNode* Node)
	{
		OnNodeDisplay.Broadcast(Node);
	}

	UFUNCTION(BlueprintCallable, Category = ConversationSystem)
	void SendReplyOptions(UConversationReply* Reply) {
		OnReplyOptionsSent.Broadcast(Reply);
	}

public:
	UPROPERTY(BlueprintAssignable)
	FOnConversationStatusUpdated OnConversationStatusUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnReplyOptionsReceived OnReplyOptionsSent;

	UPROPERTY(BlueprintAssignable)
	FOnNodeDisplay OnNodeDisplay;
};
