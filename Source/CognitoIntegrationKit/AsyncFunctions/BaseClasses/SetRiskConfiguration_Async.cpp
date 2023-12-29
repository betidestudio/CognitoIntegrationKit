
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "SetRiskConfiguration_Async.h"

#include "aws/cognito-idp/model/SetRiskConfigurationRequest.h"

USetRiskConfiguration_Async* USetRiskConfiguration_Async::SetRiskConfiguration_Async(FSetRiskConfigurationRequest Request)
{
    USetRiskConfiguration_Async* Node = NewObject<USetRiskConfiguration_Async>();
    Node->Var_Request = Request;
    return Node;
}

void USetRiskConfiguration_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::SetRiskConfigurationRequest SetRiskConfigurationRequest;
    SetRiskConfigurationRequest.SetClientId(TCHAR_TO_UTF8(*Var_Request.ClientId));
    SetRiskConfigurationRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_Request.UserPoolId));
    SetRiskConfigurationRequest.SetRiskExceptionConfiguration(Var_Request.RiskExceptionConfiguration.ToRiskExceptionConfigurationType());
    SetRiskConfigurationRequest.SetAccountTakeoverRiskConfiguration(Var_Request.AccountTakeoverRiskConfiguration.ToAccountTakeoverRiskConfigurationType());
    SetRiskConfigurationRequest.SetCompromisedCredentialsRiskConfiguration(Var_Request.CompromisedCredentialsRiskConfiguration.ToCompromisedCredentialsRiskConfigurationType());
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SetRiskConfigurationRequest&, const Aws::CognitoIdentityProvider::Model::SetRiskConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetRiskConfiguration(),FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FRiskConfigurationType(),Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->SetRiskConfigurationAsync(SetRiskConfigurationRequest, AsyncCallback);
}

void USetRiskConfiguration_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FRiskConfigurationType(),Error);
}
