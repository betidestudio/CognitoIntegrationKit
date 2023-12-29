
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminDeleteUserAttributes_Async.h"

#include "aws/cognito-idp/model/AdminDeleteUserAttributesRequest.h"

UAdminDeleteUserAttributes_Async* UAdminDeleteUserAttributes_Async::AdminDeleteUserAttributes_Async(TArray<FString> UserAttributeNames, FString Username, FString UserPoolId)
{
    UAdminDeleteUserAttributes_Async* Node = NewObject<UAdminDeleteUserAttributes_Async>();
    Node->Var_UserAttributeNames = UserAttributeNames;
    Node->Var_Username = Username;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAdminDeleteUserAttributes_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminDeleteUserAttributesRequest AdminDeleteUserAttributesRequest;
    for (FString UserAttributeName : Var_UserAttributeNames)
    {
        AdminDeleteUserAttributesRequest.AddUserAttributeNames(TCHAR_TO_UTF8(*UserAttributeName));
    }
    AdminDeleteUserAttributesRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminDeleteUserAttributesRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminDeleteUserAttributesRequest&, const Aws::CognitoIdentityProvider::Model::AdminDeleteUserAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AdminDeleteUserAttributesAsync(AdminDeleteUserAttributesRequest, AsyncCallback);
}

void UAdminDeleteUserAttributes_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
