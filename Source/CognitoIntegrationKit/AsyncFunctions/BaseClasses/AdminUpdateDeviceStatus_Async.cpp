
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminUpdateDeviceStatus_Async.h"

#include "aws/cognito-idp/model/AdminUpdateDeviceStatusRequest.h"

UAdminUpdateDeviceStatus_Async* UAdminUpdateDeviceStatus_Async::AdminUpdateDeviceStatus_Async(FString DeviceKey, TEnumAsByte<EDeviceRememberedStatus> DeviceRememberedStatus, FString UserPoolId, FString Username)
{
    UAdminUpdateDeviceStatus_Async* Node = NewObject<UAdminUpdateDeviceStatus_Async>();
    Node->Var_DeviceKey = DeviceKey;
    Node->Var_DeviceRememberedStatus = DeviceRememberedStatus;
    Node->Var_UserPoolId = UserPoolId;
    Node->Var_Username = Username;
    return Node;
}

void UAdminUpdateDeviceStatus_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminUpdateDeviceStatusRequest AdminUpdateDeviceStatusRequest;
    AdminUpdateDeviceStatusRequest.SetDeviceKey(TCHAR_TO_UTF8(*Var_DeviceKey));
    AdminUpdateDeviceStatusRequest.SetDeviceRememberedStatus(static_cast<Aws::CognitoIdentityProvider::Model::DeviceRememberedStatusType>(Var_DeviceRememberedStatus.GetValue()));\
    AdminUpdateDeviceStatusRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    AdminUpdateDeviceStatusRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminUpdateDeviceStatusRequest&, const Aws::CognitoIdentityProvider::Model::AdminUpdateDeviceStatusOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminUpdateDeviceStatusAsync(AdminUpdateDeviceStatusRequest, AsyncCallback);
}

void UAdminUpdateDeviceStatus_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
