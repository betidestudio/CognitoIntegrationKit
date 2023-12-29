
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "GetDevice_Async.h"

#include "aws/cognito-idp/model/GetDeviceRequest.h"

UGetDevice_Async* UGetDevice_Async::GetDevice_Async(FString AccessToken, FString DeviceKey)
{
    UGetDevice_Async* Node = NewObject<UGetDevice_Async>();
    Node->Var_AccessToken = AccessToken;
    Node->Var_DeviceKey = DeviceKey;
    return Node;
}

void UGetDevice_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::GetDeviceRequest GetDeviceRequest;
    GetDeviceRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    GetDeviceRequest.SetDeviceKey(TCHAR_TO_UTF8(*Var_DeviceKey));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetDeviceRequest&, const Aws::CognitoIdentityProvider::Model::GetDeviceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetDevice(),FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FDeviceType(),Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->GetDeviceAsync(GetDeviceRequest, AsyncCallback);
}

void UGetDevice_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FDeviceType(),Error);
}
