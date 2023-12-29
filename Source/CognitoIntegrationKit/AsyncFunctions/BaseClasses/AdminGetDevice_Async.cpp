
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminGetDevice_Async.h"

#include "aws/cognito-idp/model/AdminGetDeviceRequest.h"

UAdminGetDevice_Async* UAdminGetDevice_Async::AdminGetDevice_Async(FString DeviceKey, FString Username, FString UserPoolId)
{
    UAdminGetDevice_Async* Node = NewObject<UAdminGetDevice_Async>();
    Node->Var_DeviceKey = DeviceKey;
    Node->Var_Username = Username;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminGetDevice_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminGetDeviceRequest AdminGetDeviceRequest;
    AdminGetDeviceRequest.SetDeviceKey(TCHAR_TO_UTF8(*Var_DeviceKey));
    AdminGetDeviceRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminGetDeviceRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminGetDeviceRequest&, const Aws::CognitoIdentityProvider::Model::AdminGetDeviceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                FDeviceType DeviceType(outcome.GetResult().GetDevice());
                OnSuccess.Broadcast(DeviceType, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FDeviceType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->AdminGetDeviceAsync(AdminGetDeviceRequest, AsyncCallback);
}

void UAdminGetDevice_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FDeviceType(), Error);
}
