
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "SetUserSettings_Async.h"

#include "aws/cognito-idp/model/SetUserSettingsRequest.h"

USetUserSettings_Async* USetUserSettings_Async::SetUserSettings_Async(FString AccessToken, TArray<FMFAOptionType> MFAOptions)
{
    USetUserSettings_Async* Node = NewObject<USetUserSettings_Async>();
    Node->Var_AccessToken = AccessToken;
    Node->Var_MFAOptions = MFAOptions;
    return Node;
}

void USetUserSettings_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::SetUserSettingsRequest SetUserSettingsRequest;
    SetUserSettingsRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    for (int i = 0; i < Var_MFAOptions.Num(); i++)
    {
        SetUserSettingsRequest.AddMFAOptions(Var_MFAOptions[i].ToMFAOptionType());
    }
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SetUserSettingsRequest&, const Aws::CognitoIdentityProvider::Model::SetUserSettingsOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->SetUserSettingsAsync(SetUserSettingsRequest, AsyncCallback);
}

void USetUserSettings_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
