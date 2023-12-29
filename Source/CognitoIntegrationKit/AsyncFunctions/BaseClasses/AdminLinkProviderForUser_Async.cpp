
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminLinkProviderForUser_Async.h"

#include "aws/cognito-idp/model/AdminLinkProviderForUserRequest.h"

UAdminLinkProviderForUser_Async* UAdminLinkProviderForUser_Async::AdminLinkProviderForUser_Async(FAdminLinkProviderRequest AdminLinkProviderRequest)
{
    UAdminLinkProviderForUser_Async* Node = NewObject<UAdminLinkProviderForUser_Async>();
    Node->Var_AdminLinkProviderRequest = AdminLinkProviderRequest;
    return Node;
}

void UAdminLinkProviderForUser_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminLinkProviderForUserRequest AdminLinkProviderForUserRequest;
    AdminLinkProviderForUserRequest.SetDestinationUser(Var_AdminLinkProviderRequest.DestinationUser.ToProviderUserIdentifierType());
    AdminLinkProviderForUserRequest.SetSourceUser(Var_AdminLinkProviderRequest.SourceUser.ToProviderUserIdentifierType());
    AdminLinkProviderForUserRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_AdminLinkProviderRequest.UserPoolId));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminLinkProviderForUserRequest&, const Aws::CognitoIdentityProvider::Model::AdminLinkProviderForUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminLinkProviderForUserAsync(AdminLinkProviderForUserRequest, AsyncCallback);
    
}

void UAdminLinkProviderForUser_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
