
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminListDevices_Async.h"

#include "aws/cognito-idp/model/AdminListDevicesRequest.h"

UAdminListDevices_Async* UAdminListDevices_Async::AdminListDevices_Async(int32 Limit, FString PaginationToken, FString Username, FString UserPoolId)
{
    UAdminListDevices_Async* Node = NewObject<UAdminListDevices_Async>();
    Node->Var_Limit = Limit;
    Node->Var_PaginationToken = PaginationToken;
    Node->Var_Username = Username;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminListDevices_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminListDevicesRequest AdminListDevicesRequest;
    AdminListDevicesRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminListDevicesRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    AdminListDevicesRequest.SetLimit(Var_Limit);
    AdminListDevicesRequest.SetPaginationToken(TCHAR_TO_UTF8(*Var_PaginationToken));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminListDevicesRequest&, const Aws::CognitoIdentityProvider::Model::AdminListDevicesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                FAdminListDevicesResult Result;
                for (auto Device : outcome.GetResult().GetDevices())
                {
                    Result.Devices.Add(FDeviceType(Device));
                }
                Result.PaginationToken = FString(outcome.GetResult().GetPaginationToken().c_str());
                OnSuccess.Broadcast(Result, FCognitoError());
                
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FAdminListDevicesResult(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->AdminListDevicesAsync(AdminListDevicesRequest, AsyncCallback);
    
}

void UAdminListDevices_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FAdminListDevicesResult(), Error);
}
