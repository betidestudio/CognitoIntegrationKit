
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "UntagResource_Async.h"

#include "aws/cognito-identity/model/UntagResourceRequest.h"

UUntagResource_Async* UUntagResource_Async::UntagResource_Async(FString Resource_ARN,TArray<FString> TagKeys)
{
    UUntagResource_Async* Node = NewObject<UUntagResource_Async>();
    Node->Var_Resource_ARN = Resource_ARN;
    Node->Var_TagKeys = TagKeys;
    return Node;
}

void UUntagResource_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentity::Model::UntagResourceRequest UnTagRequest;
    UnTagRequest.SetResourceArn(TCHAR_TO_UTF8(*Var_Resource_ARN));
    for (int i = 0; i < Var_TagKeys.Num(); i++)
    {
        UnTagRequest.AddTagKeys(TCHAR_TO_UTF8(*Var_TagKeys[i]));
    }
    
    /*auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UntagResourceRequest&, const Aws::CognitoIdentityProvider::Model::UntagResourceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->UntagResourceAsync(UnTagRequest, AsyncCallback);  */

}

void UUntagResource_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
