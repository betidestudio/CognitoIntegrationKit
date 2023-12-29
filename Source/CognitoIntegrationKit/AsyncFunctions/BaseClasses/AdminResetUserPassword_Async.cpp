
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminResetUserPassword_Async.h"

#include "aws/cognito-idp/model/AdminResetUserPasswordRequest.h"

UAdminResetUserPassword_Async* UAdminResetUserPassword_Async::AdminResetUserPassword_Async(TMap<FString, FString> ClientMetaData, FString Username, FString UserPoolId)
{
    UAdminResetUserPassword_Async* Node = NewObject<UAdminResetUserPassword_Async>();
    Node->ClientMetaData = ClientMetaData;
    Node->Var_Username = Username;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminResetUserPassword_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminResetUserPasswordRequest AdminResetUserPasswordRequest;
    for(auto& Elem : ClientMetaData)
    {
        AdminResetUserPasswordRequest.AddClientMetadata(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    AdminResetUserPasswordRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminResetUserPasswordRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminResetUserPasswordRequest&, const Aws::CognitoIdentityProvider::Model::AdminResetUserPasswordOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminResetUserPasswordAsync(AdminResetUserPasswordRequest, AsyncCallback);
}

void UAdminResetUserPassword_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
