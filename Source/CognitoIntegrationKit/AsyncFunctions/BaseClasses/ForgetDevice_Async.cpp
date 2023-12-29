
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ForgetDevice_Async.h"

#include "aws/cognito-idp/model/ForgetDeviceRequest.h"

UForgetDevice_Async* UForgetDevice_Async::ForgetDevice_Async(FString AccessToken, FString DeviceKey)
{
    UForgetDevice_Async* Node = NewObject<UForgetDevice_Async>();
    Node->Var_AccessToken = AccessToken;
    Node->Var_DeviceKey = DeviceKey;
    return Node;
}

void UForgetDevice_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ForgetDeviceRequest ForgetDeviceRequest;
    ForgetDeviceRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    ForgetDeviceRequest.SetDeviceKey(TCHAR_TO_UTF8(*Var_DeviceKey));
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ForgetDeviceRequest&, const Aws::CognitoIdentityProvider::Model::ForgetDeviceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->ForgetDeviceAsync(ForgetDeviceRequest, AsyncCallback);
}

void UForgetDevice_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
