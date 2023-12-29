
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "GetIdentityProviderByIdentifier_Async.h"

#include "aws/cognito-idp/model/GetIdentityProviderByIdentifierRequest.h"

UGetIdentityProviderByIdentifier_Async* UGetIdentityProviderByIdentifier_Async::GetIdentityProviderByIdentifier_Async(FString IdpIdentifier, FString UserPoolId)
{
    UGetIdentityProviderByIdentifier_Async* Node = NewObject<UGetIdentityProviderByIdentifier_Async>();
    Node->Var_IdpIdentifier = IdpIdentifier;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UGetIdentityProviderByIdentifier_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::GetIdentityProviderByIdentifierRequest GetIdentityProviderByIdentifierRequest;
    GetIdentityProviderByIdentifierRequest.SetIdpIdentifier(TCHAR_TO_UTF8(*Var_IdpIdentifier));
    GetIdentityProviderByIdentifierRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetIdentityProviderByIdentifierRequest&, const Aws::CognitoIdentityProvider::Model::GetIdentityProviderByIdentifierOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetIdentityProvider(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FIdentityProviderType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->GetIdentityProviderByIdentifierAsync(GetIdentityProviderByIdentifierRequest, AsyncCallback);
}

void UGetIdentityProviderByIdentifier_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FIdentityProviderType(), Error);
}
