
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "ListDevices_Async.h"

#include "aws/cognito-idp/model/ListDevicesRequest.h"

UListDevices_Async* UListDevices_Async::ListDevices_Async(FString AccessToken, int32 Limit, FString PaginationToken)
{
    UListDevices_Async* Node = NewObject<UListDevices_Async>();
    Node->Var_AccessToken = AccessToken;
    Node->Var_Limit = Limit;
    Node->Var_PaginationToken = PaginationToken;
    return Node;
}

void UListDevices_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::ListDevicesRequest ListDevicesRequest;
    ListDevicesRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    ListDevicesRequest.SetLimit(Var_Limit);
    ListDevicesRequest.SetPaginationToken(TCHAR_TO_UTF8(*Var_PaginationToken));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::ListDevicesRequest&, const Aws::CognitoIdentityProvider::Model::ListDevicesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FDeviceType> Devices;
                for (auto Device : outcome.GetResult().GetDevices())
                {
                    FDeviceType DeviceType = Device;
                    Devices.Add(DeviceType);
                }
                OnSuccess.Broadcast(Devices, FString(outcome.GetResult().GetPaginationToken().c_str()), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(TArray<FDeviceType>(), FString(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->ListDevicesAsync(ListDevicesRequest, AsyncCallback);
}

void UListDevices_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(TArray<FDeviceType>(), FString(), Error);
}
