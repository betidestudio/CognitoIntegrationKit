
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "UpdateUserAttributes_Async.h"

#include "aws/cognito-idp/model/UpdateUserAttributesRequest.h"

UUpdateUserAttributes_Async* UUpdateUserAttributes_Async::UpdateUserAttributes_Async(FString AccessToken, TMap<FString, FString> ClientMetadata, TArray<FAttributeType> UserAttributes)
{
    UUpdateUserAttributes_Async* Node = NewObject<UUpdateUserAttributes_Async>();
    Node->Var_AccessToken = AccessToken;
    Node->Var_ClientMetadata = ClientMetadata;
    Node->Var_UserAttributes = UserAttributes;
    return Node;
}

void UUpdateUserAttributes_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::UpdateUserAttributesRequest UpdateUserAttributesRequest;
    UpdateUserAttributesRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    for (auto& Elem : Var_ClientMetadata)
    {
        UpdateUserAttributesRequest.AddClientMetadata(TCHAR_TO_UTF8(*Elem.Key), TCHAR_TO_UTF8(*Elem.Value));
    }
    for (auto& Elem : Var_UserAttributes)
    {
        UpdateUserAttributesRequest.AddUserAttributes(Elem.ToAttributeType());
    }
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateUserAttributesRequest&, const Aws::CognitoIdentityProvider::Model::UpdateUserAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FCodeDeliveryDetailsType> CodeDeliveryDetails;
                for (auto& Elem : outcome.GetResult().GetCodeDeliveryDetailsList())
                {
                    CodeDeliveryDetails.Add(FCodeDeliveryDetailsType(Elem));
                }
                OnSuccess.Broadcast(CodeDeliveryDetails, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(TArray<FCodeDeliveryDetailsType>(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->UpdateUserAttributesAsync(UpdateUserAttributesRequest, AsyncCallback);
}

void UUpdateUserAttributes_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(TArray<FCodeDeliveryDetailsType>(), Error);
}
