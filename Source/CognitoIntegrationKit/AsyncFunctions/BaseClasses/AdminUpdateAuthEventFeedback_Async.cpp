
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminUpdateAuthEventFeedback_Async.h"

#include "aws/cognito-idp/model/AdminUpdateAuthEventFeedbackRequest.h"

UAdminUpdateAuthEventFeedback_Async* UAdminUpdateAuthEventFeedback_Async::AdminUpdateAuthEventFeedback_Async(FString EventID, TEnumAsByte<EFeedbackValueType> FeedbackValue, FString UserPoolId, FString Username)
{
    UAdminUpdateAuthEventFeedback_Async* Node = NewObject<UAdminUpdateAuthEventFeedback_Async>();
    Node->Var_EventID = EventID;
    Node->Var_FeedbackValue = FeedbackValue;
    Node->Var_UserPoolId = UserPoolId;
    Node->Var_Username = Username;
    return Node;
}

void UAdminUpdateAuthEventFeedback_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminUpdateAuthEventFeedbackRequest AdminUpdateAuthEventFeedbackRequest;
    AdminUpdateAuthEventFeedbackRequest.SetEventId(TCHAR_TO_UTF8(*Var_EventID));
    AdminUpdateAuthEventFeedbackRequest.SetFeedbackValue(static_cast<Aws::CognitoIdentityProvider::Model::FeedbackValueType>(Var_FeedbackValue.GetValue()));
    AdminUpdateAuthEventFeedbackRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    AdminUpdateAuthEventFeedbackRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminUpdateAuthEventFeedbackRequest&, const Aws::CognitoIdentityProvider::Model::AdminUpdateAuthEventFeedbackOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminUpdateAuthEventFeedbackAsync(AdminUpdateAuthEventFeedbackRequest, AsyncCallback);
}

void UAdminUpdateAuthEventFeedback_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
