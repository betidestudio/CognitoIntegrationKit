
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "InitiateAuth_Async.h"

#include "aws/cognito-idp/model/InitiateAuthRequest.h"

UInitiateAuth_Async* UInitiateAuth_Async::InitiateAuth_Async(FInitiateAuthRequest Request)
{
    UInitiateAuth_Async* Node = NewObject<UInitiateAuth_Async>();
    Node->Var_InitiateAuthRequest = Request;
    return Node;
}

void UInitiateAuth_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::InitiateAuthRequest InitiateAuthRequest;
    InitiateAuthRequest.SetClientId(TCHAR_TO_UTF8(*Var_InitiateAuthRequest.ClientId));
    InitiateAuthRequest.SetAuthFlow(Aws::CognitoIdentityProvider::Model::AuthFlowTypeMapper::GetAuthFlowTypeForName(TCHAR_TO_UTF8(*Var_InitiateAuthRequest.AuthFlow)));
    for (auto& Elem : Var_InitiateAuthRequest.AuthParameters)
    {
        InitiateAuthRequest.AddAuthParameters(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    for (auto& Elem : Var_InitiateAuthRequest.ClientMetadata)
    {
        InitiateAuthRequest.AddClientMetadata(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    InitiateAuthRequest.SetAnalyticsMetadata(Var_InitiateAuthRequest.Metadata.ToAnalyticsMetadataType());
    InitiateAuthRequest.SetUserContextData(Var_InitiateAuthRequest.UserContextData.ToUserContextDataType());

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::InitiateAuthRequest&, const Aws::CognitoIdentityProvider::Model::InitiateAuthOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                FInitiateAuthResponse Response;
                Response.AuthenticationResult = outcome.GetResult().GetAuthenticationResult();
                Response.ChallengeName = static_cast<EChallengeNameType>(outcome.GetResult().GetChallengeName());
                for (auto& Elem : outcome.GetResult().GetChallengeParameters())
                {
                    Response.ChallengeParameters.Add(Elem.first.c_str(), Elem.second.c_str());
                }
                Response.Session = outcome.GetResult().GetSession().c_str();
                OnSuccess.Broadcast(Response, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FInitiateAuthResponse(),Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->InitiateAuthAsync(InitiateAuthRequest, AsyncCallback);
}

void UInitiateAuth_Async::ExecuteFailure(FCognitoError Error)
{
}
