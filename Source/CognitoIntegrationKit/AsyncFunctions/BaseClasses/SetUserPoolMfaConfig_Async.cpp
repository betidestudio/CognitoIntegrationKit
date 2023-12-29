
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "SetUserPoolMfaConfig_Async.h"

#include "aws/cognito-idp/model/SetUserPoolMfaConfigRequest.h"

USetUserPoolMfaConfig_Async* USetUserPoolMfaConfig_Async::SetUserPoolMfaConfig_Async(FSetUserPoolMfaConfigReq Request)
{
    USetUserPoolMfaConfig_Async* Node = NewObject<USetUserPoolMfaConfig_Async>();
    Node->Var_Request = Request;
    return Node;
}

void USetUserPoolMfaConfig_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::SetUserPoolMfaConfigRequest SetUserPoolMfaConfigRequest;
    SetUserPoolMfaConfigRequest.SetMfaConfiguration(static_cast<Aws::CognitoIdentityProvider::Model::UserPoolMfaType>(Var_Request.MfaConfiguration.GetValue()));
    SetUserPoolMfaConfigRequest.SetSmsMfaConfiguration(Var_Request.SmsMfaConfiguration.ToSmsMfaConfigType());
    SetUserPoolMfaConfigRequest.SetSoftwareTokenMfaConfiguration(Var_Request.SoftwareTokenMfaConfiguration.ToSoftwareTokenMfaConfigType());
    SetUserPoolMfaConfigRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_Request.UserPoolId));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SetUserPoolMfaConfigRequest&, const Aws::CognitoIdentityProvider::Model::SetUserPoolMfaConfigOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(static_cast<EUserPoolMfaType>(outcome.GetResult().GetMfaConfiguration()), outcome.GetResult().GetSmsMfaConfiguration(), outcome.GetResult().GetSoftwareTokenMfaConfiguration(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(EUserPoolMfaType::NOT_SET23, FSmsMfaConfigType(), FSoftwareTokenMfaConfigType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->SetUserPoolMfaConfigAsync(SetUserPoolMfaConfigRequest, AsyncCallback);
}

void USetUserPoolMfaConfig_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(EUserPoolMfaType::NOT_SET23, FSmsMfaConfigType(), FSoftwareTokenMfaConfigType(), Error);
}
