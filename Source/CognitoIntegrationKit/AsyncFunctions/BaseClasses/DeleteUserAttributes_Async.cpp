
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DeleteUserAttributes_Async.h"

#include "aws/cognito-idp/model/DeleteUserAttributesRequest.h"

UDeleteUserAttributes_Async* UDeleteUserAttributes_Async::DeleteUserAttributes_Async(FString AccessToken, TArray<FString> UserAttributeNames)
{
    UDeleteUserAttributes_Async* Node = NewObject<UDeleteUserAttributes_Async>();
    Node->Var_AccessToken = AccessToken;
    Node->Var_UserAttributeNames = UserAttributeNames;
    return Node;
}

void UDeleteUserAttributes_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DeleteUserAttributesRequest DeleteUserAttributesRequest;
    DeleteUserAttributesRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    for (int i = 0; i < Var_UserAttributeNames.Num(); i++)
    {
        DeleteUserAttributesRequest.AddUserAttributeNames(TCHAR_TO_UTF8(*Var_UserAttributeNames[i]));
    }
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DeleteUserAttributesRequest&, const Aws::CognitoIdentityProvider::Model::DeleteUserAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->DeleteUserAttributesAsync(DeleteUserAttributesRequest, AsyncCallback);
}

void UDeleteUserAttributes_Async::ExecuteFailure(FCognitoError Error)
{
}
