
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "GetUICustomization_Async.h"

#include "aws/cognito-idp/model/GetUICustomizationRequest.h"

UGetUICustomization_Async* UGetUICustomization_Async::GetUICustomization_Async(FString ClientId, FString UsePoolId)
{
    UGetUICustomization_Async* Node = NewObject<UGetUICustomization_Async>();
    Node->Var_ClientId = ClientId;
    Node->Var_UsePoolId = UsePoolId;
    return Node;
}

void UGetUICustomization_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::GetUICustomizationRequest GetUICustomizationRequest;
    GetUICustomizationRequest.SetClientId(TCHAR_TO_UTF8(*Var_ClientId));
    GetUICustomizationRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UsePoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetUICustomizationRequest&, const Aws::CognitoIdentityProvider::Model::GetUICustomizationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FCognitoError(), outcome.GetResult().GetUICustomization());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(Error, FUICustomizationType());
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->GetUICustomizationAsync(GetUICustomizationRequest, AsyncCallback);
}

void UGetUICustomization_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error, FUICustomizationType());
}
