
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ConfirmDevice_Async.h"

#include "aws/cognito-idp/model/ConfirmDeviceRequest.h"

UConfirmDevice_Async* UConfirmDevice_Async::ConfirmDevice_Async(FString AccessToken, FString DeviceKey, FDeviceSecretVerifierConfigType DeviceSecretVerifierConfig, FString DeviceName)
{
    UConfirmDevice_Async* Node = NewObject<UConfirmDevice_Async>();
    Node->Var_AccessToken = AccessToken;
    Node->Var_DeviceKey = DeviceKey;
    Node->Var_DeviceSecretVerifierConfig = DeviceSecretVerifierConfig;
    Node->Var_DeviceName = DeviceName;
    return Node;
}

void UConfirmDevice_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ConfirmDeviceRequest ConfirmDeviceRequest;
    ConfirmDeviceRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    ConfirmDeviceRequest.SetDeviceKey(TCHAR_TO_UTF8(*Var_DeviceKey));
    ConfirmDeviceRequest.SetDeviceSecretVerifierConfig(Var_DeviceSecretVerifierConfig.ToDeviceSecretVerifierConfigType());
    ConfirmDeviceRequest.SetDeviceName(TCHAR_TO_UTF8(*Var_DeviceName));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ConfirmDeviceRequest&, const Aws::CognitoIdentityProvider::Model::ConfirmDeviceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetUserConfirmationNecessary(),FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(false,Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ConfirmDeviceAsync(ConfirmDeviceRequest, AsyncCallback);
}

void UConfirmDevice_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(false,Error);
}
