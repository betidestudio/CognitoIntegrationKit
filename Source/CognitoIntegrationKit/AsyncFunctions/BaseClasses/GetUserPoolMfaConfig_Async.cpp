
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "GetUserPoolMfaConfig_Async.h"

#include "aws/cognito-idp/model/GetUserPoolMfaConfigRequest.h"

UGetUserPoolMfaConfig_Async* UGetUserPoolMfaConfig_Async::GetUserPoolMfaConfig_Async(FString UserPoolID)
{
    UGetUserPoolMfaConfig_Async* Node = NewObject<UGetUserPoolMfaConfig_Async>();
    Node->Var_UserPoolID = UserPoolID;
    return Node;
}

void UGetUserPoolMfaConfig_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::GetUserPoolMfaConfigRequest GetUserPoolMfaConfigRequest;
    GetUserPoolMfaConfigRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolID));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetUserPoolMfaConfigRequest&, const Aws::CognitoIdentityProvider::Model::GetUserPoolMfaConfigOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(static_cast<int32>(outcome.GetResult().GetMfaConfiguration()), outcome.GetResult().GetSmsMfaConfiguration(), outcome.GetResult().GetSoftwareTokenMfaConfiguration(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(0, FSmsMfaConfigType(), FSoftwareTokenMfaConfigType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->GetUserPoolMfaConfigAsync(GetUserPoolMfaConfigRequest, AsyncCallback);
}

void UGetUserPoolMfaConfig_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(0, FSmsMfaConfigType(), FSoftwareTokenMfaConfigType(), Error);
}
