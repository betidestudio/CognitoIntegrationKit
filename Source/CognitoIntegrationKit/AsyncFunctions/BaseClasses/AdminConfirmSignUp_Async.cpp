
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminConfirmSignUp_Async.h"

#include "aws/cognito-idp/model/AdminConfirmSignUpRequest.h"

UAdminConfirmSignUp_Async* UAdminConfirmSignUp_Async::AdminConfirmSignUp_Async(FString Username, FString UserPoolId, TMap<FString, FString> ClientMetadata)
{
    UAdminConfirmSignUp_Async* Node = NewObject<UAdminConfirmSignUp_Async>();
    Node->Var_Username = Username;
    Node->Var_UserPoolId = UserPoolId;
    Node->Var_ClientMetadata = ClientMetadata;
    return Node;
}

void UAdminConfirmSignUp_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminConfirmSignUpRequest AdminConfirmSignUpRequest;
    AdminConfirmSignUpRequest.WithUsername(TCHAR_TO_UTF8(*Var_Username));
    AdminConfirmSignUpRequest.WithUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    for(auto& it : Var_ClientMetadata)
    {
        AdminConfirmSignUpRequest.AddClientMetadata(TCHAR_TO_UTF8(*it.Key), TCHAR_TO_UTF8(*it.Value));
    }
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminConfirmSignUpRequest&, const Aws::CognitoIdentityProvider::Model::AdminConfirmSignUpOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if(outcome.IsSuccess())
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
    CognitoObject->Var_CognitoIPClient->AdminConfirmSignUpAsync(AdminConfirmSignUpRequest, AsyncCallback);
    
}

void UAdminConfirmSignUp_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
