
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "CreateResourceServer_Async.h"

#include "aws/cognito-idp/model/CreateResourceServerRequest.h"

UCreateResourceServer_Async* UCreateResourceServer_Async::CreateResourceServer_Async(FString UserPoolId, FString Identifier, FString Name, TArray<FResourceServerScopeType> ScopeType)
{
    UCreateResourceServer_Async* Node = NewObject<UCreateResourceServer_Async>();
    Node->Var_UserPoolId = UserPoolId;
    Node->Var_Identifier = Identifier;
    Node->Var_Name = Name;
    Node->Var_ScopeType = ScopeType;
    return Node;
}

void UCreateResourceServer_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::CreateResourceServerRequest CreateResourceServerRequest;
    CreateResourceServerRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    CreateResourceServerRequest.SetIdentifier(TCHAR_TO_UTF8(*Var_Identifier));
    CreateResourceServerRequest.SetName(TCHAR_TO_UTF8(*Var_Name));
    for (auto& Scope : Var_ScopeType)
    {
        CreateResourceServerRequest.AddScopes(Scope.ToResourceServerScopeType());
    }
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::CreateResourceServerRequest&, const Aws::CognitoIdentityProvider::Model::CreateResourceServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->CreateResourceServerAsync(CreateResourceServerRequest, AsyncCallback);
    
    
}

void UCreateResourceServer_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FResourceServerType(), Error);
}
