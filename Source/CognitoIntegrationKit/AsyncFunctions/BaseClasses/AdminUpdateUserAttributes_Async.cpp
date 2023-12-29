
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminUpdateUserAttributes_Async.h"

#include "aws/cognito-idp/model/AdminUpdateUserAttributesRequest.h"

UAdminUpdateUserAttributes_Async* UAdminUpdateUserAttributes_Async::AdminUpdateUserAttributes_Async()
{
    UAdminUpdateUserAttributes_Async* Node = NewObject<UAdminUpdateUserAttributes_Async>();
    return Node;
}

void UAdminUpdateUserAttributes_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminUpdateUserAttributesRequest AdminUpdateUserAttributesRequest;
    AdminUpdateUserAttributesRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminUpdateUserAttributesRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    for (auto& Attribute : Var_AttributesToUpdate)
    {
        AdminUpdateUserAttributesRequest.AddUserAttributes(Attribute.ToAttributeType());
    }
    for (auto& Metadata : Var_ClientMetadata)
    {
        AdminUpdateUserAttributesRequest.AddClientMetadata(TCHAR_TO_UTF8(*Metadata.Key), TCHAR_TO_UTF8(*Metadata.Value));
    }
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminUpdateUserAttributesRequest&, const Aws::CognitoIdentityProvider::Model::AdminUpdateUserAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminUpdateUserAttributesAsync(AdminUpdateUserAttributesRequest, AsyncCallback);
}

void UAdminUpdateUserAttributes_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
