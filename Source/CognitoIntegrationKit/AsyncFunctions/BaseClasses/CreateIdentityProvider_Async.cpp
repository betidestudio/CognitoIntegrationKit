
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "CreateIdentityProvider_Async.h"

#include "aws/cognito-idp/model/CreateIdentityProviderRequest.h"

UCreateIdentityProvider_Async* UCreateIdentityProvider_Async::CreateIdentityProvider_Async(FCreateIdentityProviderRequest Request)
{
    UCreateIdentityProvider_Async* Node = NewObject<UCreateIdentityProvider_Async>();
    Node->Var_Request = Request;
    return Node;
}

void UCreateIdentityProvider_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::CreateIdentityProviderRequest CreateIdentityProviderRequest;
    CreateIdentityProviderRequest.SetProviderName(TCHAR_TO_UTF8(*Var_Request.ProviderName));
    CreateIdentityProviderRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_Request.UserPoolId));
    CreateIdentityProviderRequest.SetProviderType(static_cast<Aws::CognitoIdentityProvider::Model::IdentityProviderTypeType>(Var_Request.ProviderType.GetValue()));
    for (auto& Elem : Var_Request.AttributeMapping)
    {
        CreateIdentityProviderRequest.AddAttributeMapping(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    for (auto& Elem : Var_Request.IdpIdentifiers)
    {
        CreateIdentityProviderRequest.AddIdpIdentifiers(TCHAR_TO_UTF8(*Elem));
    }
    for (auto& Elem : Var_Request.ProviderDetails)
    {
        CreateIdentityProviderRequest.AddProviderDetails(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::CreateIdentityProviderRequest&, const Aws::CognitoIdentityProvider::Model::CreateIdentityProviderOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->CreateIdentityProviderAsync(CreateIdentityProviderRequest, AsyncCallback);
    
}

void UCreateIdentityProvider_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FIdentityProviderType(), Error);
}
