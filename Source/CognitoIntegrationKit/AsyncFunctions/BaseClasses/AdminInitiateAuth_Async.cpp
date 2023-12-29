
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminInitiateAuth_Async.h"

#include "aws/cognito-idp/model/AdminInitiateAuthRequest.h"

UAdminInitiateAuth_Async* UAdminInitiateAuth_Async::AdminInitiateAuth_Async()
{
    UAdminInitiateAuth_Async* Node = NewObject<UAdminInitiateAuth_Async>();
    return Node;
}

void UAdminInitiateAuth_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminInitiateAuthRequest AdminInitiateAuthRequest;
    AdminInitiateAuthRequest.SetAnalyticsMetadata(Var_Request.AnalyticsMetadata.ToAnalyticsMetadataType());
    AdminInitiateAuthRequest.SetAuthFlow(static_cast<Aws::CognitoIdentityProvider::Model::AuthFlowType>(Var_Request.AuthFlow.GetValue()));
    AdminInitiateAuthRequest.SetClientId(TCHAR_TO_UTF8(*Var_Request.ClientId));
    AdminInitiateAuthRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_Request.UserPoolId));
    for (auto& Elem : Var_Request.AuthParameters)
    {
        AdminInitiateAuthRequest.AddAuthParameters(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    for (auto& Elem : Var_Request.ClientMetadata)
    {
        AdminInitiateAuthRequest.AddClientMetadata(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    AdminInitiateAuthRequest.SetContextData(Var_Request.ContextData.ToContextDataType());
    
        auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminInitiateAuthRequest&, const Aws::CognitoIdentityProvider::Model::AdminInitiateAuthOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                FAdminInitiateAuthResponse AdminInitiateAuthResponse;
                AdminInitiateAuthResponse.AuthenticationResult = outcome.GetResult().GetAuthenticationResult();
                AdminInitiateAuthResponse.ChallengeName = static_cast<EChallengeName1>(outcome.GetResult().GetChallengeName());
                for (auto& Elem : outcome.GetResult().GetChallengeParameters())
                {
                    AdminInitiateAuthResponse.ChallengeParameters.Add(Elem.first.c_str(), Elem.second.c_str());
                }
                AdminInitiateAuthResponse.Session = outcome.GetResult().GetSession().c_str();
                OnSuccess.Broadcast(AdminInitiateAuthResponse, FCognitoError());
                
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FAdminInitiateAuthResponse(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->AdminInitiateAuthAsync(AdminInitiateAuthRequest, AsyncCallback);
    
}

void UAdminInitiateAuth_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FAdminInitiateAuthResponse(), Error);
}
