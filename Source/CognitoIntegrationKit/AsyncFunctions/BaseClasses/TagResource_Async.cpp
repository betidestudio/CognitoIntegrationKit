
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "TagResource_Async.h"

#include "aws/cognito-idp/model/TagResourceRequest.h"


UTagResource_Async* UTagResource_Async::TagResource_Async(FString Resource_ARN, TMap<FString, FString> Tags)
{
	UTagResource_Async* Node = NewObject<UTagResource_Async>();
	Node->Var_Resource_ARN = Resource_ARN;
	Node->Var_Tags = Tags;
	return Node;
}

void UTagResource_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
	Aws::CognitoIdentityProvider::Model::TagResourceRequest TagResourceRequest;
	TagResourceRequest.SetResourceArn(TCHAR_TO_UTF8(*Var_Resource_ARN));
	for (auto& Elem : Var_Tags)
	{
		TagResourceRequest.AddTags(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
	}
	
	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::TagResourceRequest&, const Aws::CognitoIdentityProvider::Model::TagResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if (outcome.IsSuccess())
			{
				OnSuccess.Broadcast(FCognitoError());
			}
			else
			{
				FCognitoError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
				Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
				OnFailure.Broadcast(Error);
			}
			SetReadyToDestroy();
		});
	};
	CognitoObject->Var_CognitoIPClient->TagResourceAsync(TagResourceRequest, AsyncCallback);
}

void UTagResource_Async::ExecuteFailure(FCognitoError Error)
{
	OnFailure.Broadcast(Error);
}
