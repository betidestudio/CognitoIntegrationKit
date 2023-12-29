
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DescribeRiskConfiguration_Async.h"

#include "aws/cognito-idp/model/DescribeRiskConfigurationRequest.h"

UDescribeRiskConfiguration_Async* UDescribeRiskConfiguration_Async::DescribeRiskConfiguration_Async(FString ClientId, FString UserPoolId)
{
    UDescribeRiskConfiguration_Async* Node = NewObject<UDescribeRiskConfiguration_Async>();
    Node->Var_ClientId = ClientId;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UDescribeRiskConfiguration_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DescribeRiskConfigurationRequest DescribeRiskConfigurationRequest;
    DescribeRiskConfigurationRequest.SetClientId(TCHAR_TO_UTF8(*Var_ClientId));
    DescribeRiskConfigurationRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeRiskConfigurationRequest&, const Aws::CognitoIdentityProvider::Model::DescribeRiskConfigurationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetRiskConfiguration(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FRiskConfigurationType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->DescribeRiskConfigurationAsync(DescribeRiskConfigurationRequest, AsyncCallback);
}

void UDescribeRiskConfiguration_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FRiskConfigurationType(), Error);
}
