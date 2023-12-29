//Copyright (c) 2023 Betide Studio. All Rights Reserved.


#include "CIKAsyncFunction.h"

void UCIKAsyncFunction::Activate()
{
	FCognitoError Local_FailureResponse = FCognitoError();
	Super::Activate();
	TArray<UCIK_Object*> Objects;
	for (TObjectIterator<UCIK_Object> Itr; Itr; ++Itr)
	{
		Objects.Add(*Itr);
	}
	if(Objects[0])
	{
		if(Objects[0]->CognitoClientID.IsEmpty())
		{
			Local_FailureResponse.ErrorMessage = "Cognito Client ID is empty";
			ExecuteFailure(Local_FailureResponse);
			SetReadyToDestroy();
		}
		else
		{
			ContinueProcess(Objects[0]);
		}
	}
	else
	{
		Local_FailureResponse.ErrorMessage = "No object found";
		ExecuteFailure(Local_FailureResponse);
		SetReadyToDestroy();
	}
	
}

void UCIKAsyncFunction::ContinueProcess(UCIK_Object* CognitoObject)
{
}

void UCIKAsyncFunction::ExecuteFailure(FCognitoError Error)
{
	return;
}
