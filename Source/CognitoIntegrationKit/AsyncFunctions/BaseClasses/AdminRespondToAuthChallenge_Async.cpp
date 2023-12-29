
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminRespondToAuthChallenge_Async.h"

#include "aws/cognito-idp/model/AdminRespondToAuthChallengeRequest.h"

UAdminRespondToAuthChallenge_Async* UAdminRespondToAuthChallenge_Async::AdminRespondToAuthChallenge_Async(FAdminRespondToAuthChallengeReq Request)
{
    UAdminRespondToAuthChallenge_Async* Node = NewObject<UAdminRespondToAuthChallenge_Async>();
    Node->Val_AdminRespondToAuthChallengeReq = Request;
    return Node;
}

void UAdminRespondToAuthChallenge_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminRespondToAuthChallengeRequest AdminRespondToAuthChallengeRequest;
    AdminRespondToAuthChallengeRequest.SetAnalyticsMetadata(Val_AdminRespondToAuthChallengeReq.AnalyticsMetadata.ToAnalyticsMetadataType());
    AdminRespondToAuthChallengeRequest.SetChallengeName(static_cast<Aws::CognitoIdentityProvider::Model::ChallengeNameType>(Val_AdminRespondToAuthChallengeReq.ChallengeName.GetValue()));
    AdminRespondToAuthChallengeRequest.SetSession(TCHAR_TO_UTF8(*Val_AdminRespondToAuthChallengeReq.Session));
    AdminRespondToAuthChallengeRequest.SetClientId(TCHAR_TO_UTF8(*Val_AdminRespondToAuthChallengeReq.ClientId));
    AdminRespondToAuthChallengeRequest.SetUserPoolId(TCHAR_TO_UTF8(*Val_AdminRespondToAuthChallengeReq.UserPoolId));
    AdminRespondToAuthChallengeRequest.SetContextData(Val_AdminRespondToAuthChallengeReq.ContextData.ToContextDataType());
    for(auto Elem : Val_AdminRespondToAuthChallengeReq.ChallengeResponse)
    {
        AdminRespondToAuthChallengeRequest.AddChallengeResponses(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    for(auto Elem : Val_AdminRespondToAuthChallengeReq.ClientMetaData)
    {
        AdminRespondToAuthChallengeRequest.AddClientMetadata(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminRespondToAuthChallengeRequest&, const Aws::CognitoIdentityProvider::Model::AdminRespondToAuthChallengeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                FAdminRespondToAuthChallengeResp Data;
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
                OnFailure.Broadcast(Error, FAdminRespondToAuthChallengeResp());
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->AdminRespondToAuthChallengeAsync(AdminRespondToAuthChallengeRequest, AsyncCallback);
    
}

void UAdminRespondToAuthChallenge_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error, FAdminRespondToAuthChallengeResp());
}
