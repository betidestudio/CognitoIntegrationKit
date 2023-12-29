
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminForgetDevice_Async.h"

#include "aws/cognito-idp/model/AdminForgetDeviceRequest.h"

UAdminForgetDevice_Async* UAdminForgetDevice_Async::AdminForgetDevice_Async(FString Username, FString DeviceKey, FString UserPoolId)
{
    UAdminForgetDevice_Async* Node = NewObject<UAdminForgetDevice_Async>();
    Node->Var_Username = Username;
    Node->Var_DeviceKey = DeviceKey;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminForgetDevice_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminForgetDeviceRequest AdminForgetDeviceRequest;
    AdminForgetDeviceRequest.WithUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminForgetDeviceRequest.WithDeviceKey(TCHAR_TO_UTF8(*Var_DeviceKey));
    AdminForgetDeviceRequest.WithUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminForgetDeviceRequest&, const Aws::CognitoIdentityProvider::Model::AdminForgetDeviceOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminForgetDeviceAsync(AdminForgetDeviceRequest, AsyncCallback);
}

void UAdminForgetDevice_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
