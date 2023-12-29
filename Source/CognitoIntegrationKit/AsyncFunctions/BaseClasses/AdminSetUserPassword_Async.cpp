
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminSetUserPassword_Async.h"

#include "aws/cognito-idp/model/AdminSetUserPasswordRequest.h"

UAdminSetUserPassword_Async* UAdminSetUserPassword_Async::AdminSetUserPassword_Async(FString Password, bool Permanent, FString Username, FString UserPoolId)
{
    UAdminSetUserPassword_Async* Node = NewObject<UAdminSetUserPassword_Async>();
    Node->Var_Password = Password;
    Node->bVar_Permanent = Permanent;
    Node->Var_Username = Username;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminSetUserPassword_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminSetUserPasswordRequest AdminSetUserPasswordRequest;
    AdminSetUserPasswordRequest.SetPassword(TCHAR_TO_UTF8(*Var_Password));
    AdminSetUserPasswordRequest.SetPermanent(bVar_Permanent);
    AdminSetUserPasswordRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminSetUserPasswordRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminSetUserPasswordRequest&, const Aws::CognitoIdentityProvider::Model::AdminSetUserPasswordOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminSetUserPasswordAsync(AdminSetUserPasswordRequest, AsyncCallback);
}

void UAdminSetUserPassword_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
