
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminDisableProviderForUser_Async.h"

#include "aws/cognito-idp/model/AdminDisableProviderForUserRequest.h"

UAdminDisableProviderForUser_Async* UAdminDisableProviderForUser_Async::AdminDisableProviderForUser_Async(FProviderUserIdentifierType ProviderUserIdentifier, FString UserPoolId)
{
    UAdminDisableProviderForUser_Async* Node = NewObject<UAdminDisableProviderForUser_Async>();
    Node->Var_ProviderUserIdentifier = ProviderUserIdentifier;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminDisableProviderForUser_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminDisableProviderForUserRequest AdminDisableProviderForUserRequest;
    AdminDisableProviderForUserRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    AdminDisableProviderForUserRequest.SetUser(Var_ProviderUserIdentifier.ToProviderUserIdentifierType());

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminDisableProviderForUserRequest&, const Aws::CognitoIdentityProvider::Model::AdminDisableProviderForUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminDisableProviderForUserAsync(AdminDisableProviderForUserRequest, AsyncCallback);
}

void UAdminDisableProviderForUser_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
