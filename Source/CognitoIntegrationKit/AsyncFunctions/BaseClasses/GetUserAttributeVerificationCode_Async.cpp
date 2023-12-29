
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "GetUserAttributeVerificationCode_Async.h"

#include "aws/cognito-idp/model/GetUserAttributeVerificationCodeRequest.h"

UGetUserAttributeVerificationCode_Async* UGetUserAttributeVerificationCode_Async::GetUserAttributeVerificationCode_Async(FString AccessToken, FString AttributeName, TMap<FString,FString> ClientMetadata)
{
    UGetUserAttributeVerificationCode_Async* Node = NewObject<UGetUserAttributeVerificationCode_Async>();
    Node->Var_AccessToken = AccessToken;
    Node->Var_AttributeName = AttributeName;
    Node->Var_ClientMetadata = ClientMetadata;
    return Node;
}

void UGetUserAttributeVerificationCode_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::GetUserAttributeVerificationCodeRequest GetUserAttributeVerificationCodeRequest;
    GetUserAttributeVerificationCodeRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    GetUserAttributeVerificationCodeRequest.SetAttributeName(TCHAR_TO_UTF8(*Var_AttributeName));
    Aws::Map<Aws::String, Aws::String> ClientMetadata;
    for (auto Elem : Var_ClientMetadata)
    {
        ClientMetadata.at(TCHAR_TO_UTF8(*Elem.Key)) = TCHAR_TO_UTF8(*Elem.Value);
    }
    GetUserAttributeVerificationCodeRequest.SetClientMetadata(ClientMetadata);
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetUserAttributeVerificationCodeRequest&, const Aws::CognitoIdentityProvider::Model::GetUserAttributeVerificationCodeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetCodeDeliveryDetails(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FCodeDeliveryDetailsType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->GetUserAttributeVerificationCodeAsync(GetUserAttributeVerificationCodeRequest, AsyncCallback);
    
}

void UGetUserAttributeVerificationCode_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FCodeDeliveryDetailsType(), Error);
}
