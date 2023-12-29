
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "UpdateResourceServer_Async.h"

#include "aws/cognito-idp/model/UpdateResourceServerRequest.h"

UUpdateResourceServer_Async* UUpdateResourceServer_Async::UpdateResourceServer_Async(FUpdateResourceServerReq Request)
{
    UUpdateResourceServer_Async* Node = NewObject<UUpdateResourceServer_Async>();
    Node->Var_UpdateResourceServerRequest = Request;
    return Node;
}

void UUpdateResourceServer_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::UpdateResourceServerRequest UpdateResourceServerRequest;
    UpdateResourceServerRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UpdateResourceServerRequest.UserPoolId));
    UpdateResourceServerRequest.SetIdentifier(TCHAR_TO_UTF8(*Var_UpdateResourceServerRequest.Identifier));
    UpdateResourceServerRequest.SetName(TCHAR_TO_UTF8(*Var_UpdateResourceServerRequest.Name));
    Aws::Vector<Aws::CognitoIdentityProvider::Model::ResourceServerScopeType> Scopes;
    for (auto& Elem : Var_UpdateResourceServerRequest.Scopes)
    {
        Aws::CognitoIdentityProvider::Model::ResourceServerScopeType ResourceServerScopeType;
        Scopes.push_back(Elem.ToResourceServerScopeType());
    }
    UpdateResourceServerRequest.SetScopes(Scopes);

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateResourceServerRequest&, const Aws::CognitoIdentityProvider::Model::UpdateResourceServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetResourceServer(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FResourceServerType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->UpdateResourceServerAsync(UpdateResourceServerRequest, AsyncCallback);
}

void UUpdateResourceServer_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FResourceServerType(), Error);
}
