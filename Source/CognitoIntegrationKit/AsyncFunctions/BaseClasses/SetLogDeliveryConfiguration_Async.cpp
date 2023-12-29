
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "SetLogDeliveryConfiguration_Async.h"

#include "aws/cognito-idp/model/SetLogDeliveryConfigurationRequest.h"

USetLogDeliveryConfiguration_Async* USetLogDeliveryConfiguration_Async::SetLogDeliveryConfiguration_Async(TArray<FLogConfigurationType> LogConfigurations, FString UserPoolId)
{
    USetLogDeliveryConfiguration_Async* Node = NewObject<USetLogDeliveryConfiguration_Async>();
    Node->Var_LogConfigurations = LogConfigurations;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void USetLogDeliveryConfiguration_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::SetLogDeliveryConfigurationRequest SetLogDeliveryConfigurationRequest;
    SetLogDeliveryConfigurationRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    for (FLogConfigurationType LogConfiguration : Var_LogConfigurations)
    {
        SetLogDeliveryConfigurationRequest.AddLogConfigurations(LogConfiguration.ToLogConfigurationType());
    }
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SetLogDeliveryConfigurationRequest&, const Aws::CognitoIdentityProvider::Model::SetLogDeliveryConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FLogDeliveryConfigurationType(outcome.GetResult().GetLogDeliveryConfiguration()), FCognitoError());
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
    CognitoObject->Var_CognitoIPClient->SetLogDeliveryConfigurationAsync(SetLogDeliveryConfigurationRequest, AsyncCallback);
}

void USetLogDeliveryConfiguration_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FLogDeliveryConfigurationType(), Error);
}
