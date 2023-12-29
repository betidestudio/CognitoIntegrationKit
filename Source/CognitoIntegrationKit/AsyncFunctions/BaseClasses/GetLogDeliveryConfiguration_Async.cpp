
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "GetLogDeliveryConfiguration_Async.h"

#include "aws/cognito-idp/model/GetLogDeliveryConfigurationRequest.h"

UGetLogDeliveryConfiguration_Async* UGetLogDeliveryConfiguration_Async::GetLogDeliveryConfiguration_Async(FString UserPoolId)
{
    UGetLogDeliveryConfiguration_Async* Node = NewObject<UGetLogDeliveryConfiguration_Async>();
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UGetLogDeliveryConfiguration_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::GetLogDeliveryConfigurationRequest GetLogDeliveryConfigurationRequest;
    GetLogDeliveryConfigurationRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetLogDeliveryConfigurationRequest&, const Aws::CognitoIdentityProvider::Model::GetLogDeliveryConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetLogDeliveryConfiguration(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FLogDeliveryConfigurationType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->GetLogDeliveryConfigurationAsync(GetLogDeliveryConfigurationRequest, AsyncCallback);
}

void UGetLogDeliveryConfiguration_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FLogDeliveryConfigurationType(), Error);
}
