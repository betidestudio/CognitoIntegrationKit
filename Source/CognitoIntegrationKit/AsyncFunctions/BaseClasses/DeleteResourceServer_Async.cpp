
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DeleteResourceServer_Async.h"

#include "aws/cognito-idp/model/DeleteResourceServerRequest.h"

UDeleteResourceServer_Async* UDeleteResourceServer_Async::DeleteResourceServer_Async(FString UserPoolId, FString Identifier)
{
    UDeleteResourceServer_Async* Node = NewObject<UDeleteResourceServer_Async>();
    Node->Var_Identifer = Identifier;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UDeleteResourceServer_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DeleteResourceServerRequest DeleteResourceServerRequest;
    DeleteResourceServerRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    DeleteResourceServerRequest.SetIdentifier(TCHAR_TO_UTF8(*Var_Identifer));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteResourceServerRequest&, const Aws::CognitoIdentityProvider::Model::DeleteResourceServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->DeleteResourceServerAsync(DeleteResourceServerRequest, AsyncCallback);
}

void UDeleteResourceServer_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
