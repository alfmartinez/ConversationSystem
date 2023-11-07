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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConversationStatusUpdated, EConversationStatus, Status);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConversationReplySent, FName, ReplyName);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnReplyOptionsReceived, UConversationReply*, Options);

/**
 * 
 */
UCLASS()
class CONVERSATIONSYSTEM_API UConversationSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = ConversationSystem)
	void StartConversation() {
		OnConversationStatusUpdated.Broadcast(EConversationStatus::STARTED);
	}

	UFUNCTION(BlueprintCallable, Category = ConversationSystem)
	void FinishConversation() {
		OnConversationStatusUpdated.Broadcast(EConversationStatus::COMPLETED);
	}

	UFUNCTION(BlueprintCallable, Category = ConversationSystem)
	void AbortConversation() {
		OnConversationStatusUpdated.Broadcast(EConversationStatus::ABORTED);
	}

	UFUNCTION(BlueprintCallable, Category = ConversationSystem)
	void SendReplyOptions(UConversationReply* Reply) {
		OnReplyOptionsSent.Broadcast(Reply);
	}


public:
	UPROPERTY(BlueprintAssignable)
	FOnConversationStatusUpdated OnConversationStatusUpdated;

	UPROPERTY(BlueprintAssignable)
	FOnConversationReplySent OnReplySent;

	UPROPERTY(BlueprintAssignable)
	FOnReplyOptionsReceived OnReplyOptionsSent;
};
