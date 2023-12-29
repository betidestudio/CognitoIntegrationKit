
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "UpdateDeviceStatus_Async.h"

#include "aws/cognito-idp/model/UpdateDeviceStatusRequest.h"

UUpdateDeviceStatus_Async* UUpdateDeviceStatus_Async::UpdateDeviceStatus_Async(FUpdateDeviceStatusReq UpdateDeviceStatusReq)
{
    UUpdateDeviceStatus_Async* Node = NewObject<UUpdateDeviceStatus_Async>();
    Node->Var_UpdateDeviceStatusReq = UpdateDeviceStatusReq;
    return Node;
}

void UUpdateDeviceStatus_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::UpdateDeviceStatusRequest UpdateDeviceStatusRequest;
    UpdateDeviceStatusRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_UpdateDeviceStatusReq.AccessToken));
    UpdateDeviceStatusRequest.SetDeviceKey(TCHAR_TO_UTF8(*Var_UpdateDeviceStatusReq.DeviceToken));
    switch (Var_UpdateDeviceStatusReq.DeviceRememberedStatus)
    {
        case EDeviceRememberedStatus::remembered:
            UpdateDeviceStatusRequest.SetDeviceRememberedStatus(Aws::CognitoIdentityProvider::Model::DeviceRememberedStatusType::remembered);
            break;

        case EDeviceRememberedStatus::not_remembered:
            UpdateDeviceStatusRequest.SetDeviceRememberedStatus(Aws::CognitoIdentityProvider::Model::DeviceRememberedStatusType::not_remembered);
            break;

    case EDeviceRememberedStatus::NOT_SET29:
            UpdateDeviceStatusRequest.SetDeviceRememberedStatus(Aws::CognitoIdentityProvider::Model::DeviceRememberedStatusType::NOT_SET);
            break;
    default: ;
    }
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateDeviceStatusRequest&, const Aws::CognitoIdentityProvider::Model::UpdateDeviceStatusOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->UpdateDeviceStatusAsync(UpdateDeviceStatusRequest, AsyncCallback);
}

void UUpdateDeviceStatus_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
