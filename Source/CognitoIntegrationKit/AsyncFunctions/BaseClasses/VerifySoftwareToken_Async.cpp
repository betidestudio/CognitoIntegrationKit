
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "VerifySoftwareToken_Async.h"

#include "aws/cognito-idp/model/VerifySoftwareTokenRequest.h"

UVerifySoftwareToken_Async* UVerifySoftwareToken_Async::VerifySoftwareToken_Async(UObject* WorldContextObject, const FString& AccessToken, const FString& FriendlyDeviceName, const FString& Session, const FString& UserCode)
{
    UVerifySoftwareToken_Async* Node = NewObject<UVerifySoftwareToken_Async>();
    Node->Var_AccessToken = AccessToken;
    Node->Var_FriendlyDeviceName = FriendlyDeviceName;
    Node->Var_Session = Session;
    Node->Var_UserCode = UserCode;
    return Node;
}

void UVerifySoftwareToken_Async::Activate()
{
    FCognitoError Local_FailureResponse = FCognitoError();
    Super::Activate();
    TArray<UCIK_Object*> Objects;
    for (TObjectIterator<UCIK_Object> Itr; Itr; ++Itr)
    {
        Objects.Add(*Itr);
    }
    if(Objects[0])
    {
        if(Objects[0]->CognitoClientID.IsEmpty())
        {
            Local_FailureResponse.ErrorMessage = "Cognito Client ID is empty";
            OnFailure.Broadcast("",EResponStatus::Error_,Local_FailureResponse);
            SetReadyToDestroy();
        }
        else
        {
            ContinueProcess(Objects[0]);
        }
    }
    else
    {
        Local_FailureResponse.ErrorMessage = "No object found";
        OnFailure.Broadcast("",EResponStatus::Error_,Local_FailureResponse);
        SetReadyToDestroy();
    }
}

void UVerifySoftwareToken_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::VerifySoftwareTokenRequest VerifySoftwareTokenRequest;
    VerifySoftwareTokenRequest.SetSession(TCHAR_TO_UTF8(*Var_Session));
    VerifySoftwareTokenRequest.SetUserCode(TCHAR_TO_UTF8(*Var_UserCode));
    VerifySoftwareTokenRequest.SetFriendlyDeviceName(TCHAR_TO_UTF8(*Var_FriendlyDeviceName));
    VerifySoftwareTokenRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::VerifySoftwareTokenRequest&, const Aws::CognitoIdentityProvider::Model::VerifySoftwareTokenOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                Aws::CognitoIdentityProvider::Model::VerifySoftwareTokenResponseType ResponseType = outcome.GetResult().GetStatus();
                OnSuccess.Broadcast(outcome.GetResult().GetSession().c_str(),static_cast<EResponStatus>(outcome.GetResult().GetStatus()),FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast("",EResponStatus::Error_,Error);
            }
            SetReadyToDestroy();
        });
    };

    CognitoObject->Var_CognitoIPClient->VerifySoftwareTokenAsync(VerifySoftwareTokenRequest, AsyncCallback);
}
