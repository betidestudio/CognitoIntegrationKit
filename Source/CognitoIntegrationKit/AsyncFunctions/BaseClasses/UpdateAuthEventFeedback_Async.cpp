
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "UpdateAuthEventFeedback_Async.h"

#include "aws/cognito-idp/model/UpdateAuthEventFeedbackRequest.h"

UUpdateAuthEventFeedback_Async* UUpdateAuthEventFeedback_Async::UpdateAuthEventFeedback_Async(const FUpdateAuthEventFeedbackReq& UpdateAuthEventFeedbackReq)
{
    UUpdateAuthEventFeedback_Async* Node = NewObject<UUpdateAuthEventFeedback_Async>();
    Node->Var_UpdateAuthEventFeedbackReq = UpdateAuthEventFeedbackReq;
    return Node;
}

void UUpdateAuthEventFeedback_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::UpdateAuthEventFeedbackRequest UpdateAuthEventFeedbackRequest;
    UpdateAuthEventFeedbackRequest.SetEventId(TCHAR_TO_UTF8(*Var_UpdateAuthEventFeedbackReq.EventId));
    UpdateAuthEventFeedbackRequest.SetFeedbackToken(TCHAR_TO_UTF8(*Var_UpdateAuthEventFeedbackReq.FeedbackToken));
    UpdateAuthEventFeedbackRequest.SetUsername(TCHAR_TO_UTF8(*Var_UpdateAuthEventFeedbackReq.Username));
    UpdateAuthEventFeedbackRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UpdateAuthEventFeedbackReq.UserPoolId));
    switch (Var_UpdateAuthEventFeedbackReq.FeedbackValue)
    {
    case FFeedbackValueType::Valid1:
            UpdateAuthEventFeedbackRequest.SetFeedbackValue(Aws::CognitoIdentityProvider::Model::FeedbackValueType::Valid);
            break;
        case FFeedbackValueType::Invalid1:
            UpdateAuthEventFeedbackRequest.SetFeedbackValue(Aws::CognitoIdentityProvider::Model::FeedbackValueType::Invalid);
            break;
        case FFeedbackValueType::NOT_SET8:
            UpdateAuthEventFeedbackRequest.SetFeedbackValue(Aws::CognitoIdentityProvider::Model::FeedbackValueType::NOT_SET);
        break;
    default: ;
    }
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateAuthEventFeedbackRequest&, const Aws::CognitoIdentityProvider::Model::UpdateAuthEventFeedbackOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->UpdateAuthEventFeedbackAsync(UpdateAuthEventFeedbackRequest, AsyncCallback);
}

void UUpdateAuthEventFeedback_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
