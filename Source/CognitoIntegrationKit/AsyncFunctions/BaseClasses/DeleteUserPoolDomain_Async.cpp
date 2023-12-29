
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DeleteUserPoolDomain_Async.h"

#include "aws/cognito-idp/model/DeleteUserPoolDomainRequest.h"

UDeleteUserPoolDomain_Async* UDeleteUserPoolDomain_Async::DeleteUserPoolDomain_Async(FString Domain, FString UserPoolId)
{
    UDeleteUserPoolDomain_Async* Node = NewObject<UDeleteUserPoolDomain_Async>();
    Node->Var_Domain = Domain;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UDeleteUserPoolDomain_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DeleteUserPoolDomainRequest DeleteUserPoolDomainRequest;
    DeleteUserPoolDomainRequest.SetDomain(TCHAR_TO_UTF8(*Var_Domain));
    DeleteUserPoolDomainRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolDomainRequest&, const Aws::CognitoIdentityProvider::Model::DeleteUserPoolDomainOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->DeleteUserPoolDomainAsync(DeleteUserPoolDomainRequest, AsyncCallback);
}

void UDeleteUserPoolDomain_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
