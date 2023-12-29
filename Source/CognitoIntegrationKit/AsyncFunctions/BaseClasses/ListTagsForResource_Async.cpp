
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ListTagsForResource_Async.h"

#include "aws/cognito-idp/model/ListTagsForResourceRequest.h"

UListTagsForResource_Async* UListTagsForResource_Async::ListTagsForResource_Async(FString ResourceArn)
{
    UListTagsForResource_Async* Node = NewObject<UListTagsForResource_Async>();
    Node->Var_ResourceArn = ResourceArn;
    return Node;
}

void UListTagsForResource_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ListTagsForResourceRequest ListTagsForResourceRequest;
    ListTagsForResourceRequest.SetResourceArn(TCHAR_TO_UTF8(*Var_ResourceArn));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListTagsForResourceRequest&, const Aws::CognitoIdentityProvider::Model::ListTagsForResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                FListTagsForResourceResponse Response;
                for (auto Tag : outcome.GetResult().GetTags())
                {
                    Response.Tags.Add(FString(Tag.first.c_str()), FString(Tag.second.c_str()));
                }
                OnSuccess.Broadcast(Response, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FListTagsForResourceResponse(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ListTagsForResourceAsync(ListTagsForResourceRequest, AsyncCallback);
}

void UListTagsForResource_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FListTagsForResourceResponse(), Error);
}
