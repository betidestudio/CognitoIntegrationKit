
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "RespondToAuthChallenge_Async.h"

#include "aws/cognito-idp/model/RespondToAuthChallengeRequest.h"

URespondToAuthChallenge_Async* URespondToAuthChallenge_Async::RespondToAuthChallenge_Async(FRespondToAuthChallengeReq Request)
{
    URespondToAuthChallenge_Async* Node = NewObject<URespondToAuthChallenge_Async>();
    Node->Val_RespondToAuthChallengeReq = Request;
    return Node;
}

void URespondToAuthChallenge_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::RespondToAuthChallengeRequest RespondToAuthChallengeRequest;
    RespondToAuthChallengeRequest.SetAnalyticsMetadata(Val_RespondToAuthChallengeReq.AnalyticsMetadata.ToAnalyticsMetadataType());
    RespondToAuthChallengeRequest.SetChallengeName(static_cast<Aws::CognitoIdentityProvider::Model::ChallengeNameType>(Val_RespondToAuthChallengeReq.ChallengeName.GetValue()));
    RespondToAuthChallengeRequest.SetSession(TCHAR_TO_UTF8(*Val_RespondToAuthChallengeReq.Session));
    RespondToAuthChallengeRequest.SetClientId(TCHAR_TO_UTF8(*Val_RespondToAuthChallengeReq.ClientId));
    RespondToAuthChallengeRequest.SetUserContextData(Val_RespondToAuthChallengeReq.ContextData.ToUserContextDataType());
    for(auto Elem : Val_RespondToAuthChallengeReq.ChallengeResponse)
    {
        RespondToAuthChallengeRequest.AddChallengeResponses(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    for(auto Elem : Val_RespondToAuthChallengeReq.ClientMetaData)
    {
        RespondToAuthChallengeRequest.AddClientMetadata(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::RespondToAuthChallengeRequest&, const Aws::CognitoIdentityProvider::Model::RespondToAuthChallengeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                FRespondToAuthChallengeResp Data;
                Data.ChallengeName = static_cast<EChallengeName1>(outcome.GetResult().GetChallengeName());
                for(auto Elem : outcome.GetResult().GetChallengeParameters())
                {
                    Data.ChallengeParameters.Add(Elem.first.c_str(), Elem.second.c_str());
                }
                Data.Session = FString(outcome.GetResult().GetSession().c_str());
                Data.AuthenticationResult = outcome.GetResult().GetAuthenticationResult();
                OnSuccess.Broadcast(FCognitoError(), Data);
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(Error, FRespondToAuthChallengeResp());
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->RespondToAuthChallengeAsync(RespondToAuthChallengeRequest, AsyncCallback);
    
}

void URespondToAuthChallenge_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error, FRespondToAuthChallengeResp());
}
