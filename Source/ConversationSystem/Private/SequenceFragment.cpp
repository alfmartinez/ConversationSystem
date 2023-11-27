// Fill out your copyright notice in the Description page of Project Settings.


#include "SequenceFragment.h"

void USequenceFragment::DoProcess_Implementation(UConversationAsyncAction* InConversation)
{
	Index = 0;
	Conversation = InConversation;
	ProcessFragment();
}

void USequenceFragment::ProcessFragment()
{
	if (Fragments.IsValidIndex(Index)) {
		CurrentFragment = Fragments[Index];
		CurrentFragment->OnFragmentComplete.Clear();
		CurrentFragment->OnFragmentComplete.AddDynamic(this, &USequenceFragment::Advance);
		CurrentFragment->DoProcess(Conversation);
	}
}

void USequenceFragment::Advance(ECompletionBehavior InBehavior)
{
	switch (InBehavior) {
	case ECompletionBehavior::DO_RESTART:
		Conversation->Start();
		Complete();
		break;
	case ECompletionBehavior::DO_FINISH:
		Conversation->Finish();
		Complete();
		break;
	case ECompletionBehavior::DO_CONTINUE:
		Index++;
		if (Index > Fragments.Num())
		{
			Complete();
		}
		else {
			ProcessFragment();
		}
		break;
	}
}
