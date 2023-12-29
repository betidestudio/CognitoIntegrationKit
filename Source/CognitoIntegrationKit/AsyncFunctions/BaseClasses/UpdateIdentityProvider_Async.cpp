
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "UpdateIdentityProvider_Async.h"

#include "aws/cognito-idp/model/UpdateIdentityProviderRequest.h"

UUpdateIdentityProvider_Async* UUpdateIdentityProvider_Async::UpdateIdentityProvider_Async(FUpdateIdentityProviderReq Request)
{
    UUpdateIdentityProvider_Async* Node = NewObject<UUpdateIdentityProvider_Async>();
    Node->Var_UpdateIdentityProviderReq = Request;
    return Node;
}

void UUpdateIdentityProvider_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::UpdateIdentityProviderRequest UpdateIdentityProviderRequest;
    UpdateIdentityProviderRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UpdateIdentityProviderReq.UserPoolId));
    UpdateIdentityProviderRequest.SetProviderName(TCHAR_TO_UTF8(*Var_UpdateIdentityProviderReq.ProviderName));
    Aws::Map<Aws::String, Aws::String> ProviderDetails;
    for (auto& Elem : Var_UpdateIdentityProviderReq.ProviderDetails)
    {
        ProviderDetails.emplace(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    UpdateIdentityProviderRequest.SetProviderDetails(ProviderDetails);
    Aws::Map<Aws::String, Aws::String> AttributeMapping;
    for (auto& Elem : Var_UpdateIdentityProviderReq.AttributeMapping)
    {
        AttributeMapping.emplace(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    UpdateIdentityProviderRequest.SetAttributeMapping(AttributeMapping);
    Aws::Vector<Aws::String> IdpIdentifiers;
    for (auto& Elem : Var_UpdateIdentityProviderReq.IdpIdentifiers)
    {
        IdpIdentifiers.push_back(TCHAR_TO_UTF8(*Elem));
    }
    UpdateIdentityProviderRequest.SetIdpIdentifiers(IdpIdentifiers);

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateIdentityProviderRequest&, const Aws::CognitoIdentityProvider::Model::UpdateIdentityProviderOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FIdentityProviderType(outcome.GetResult().GetIdentityProvider()), FCognitoError());
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
    CognitoObject->Var_CognitoIPClient->UpdateIdentityProviderAsync(UpdateIdentityProviderRequest, AsyncCallback);
}

void UUpdateIdentityProvider_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FIdentityProviderType(), Error);
}
