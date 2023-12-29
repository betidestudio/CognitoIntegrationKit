
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AddCustomAttributes_Async.h"

#include "aws/cognito-idp/model/AddCustomAttributesRequest.h"

UAddCustomAttributes_Async* UAddCustomAttributes_Async::AddCustomAttributes_Async(TArray<FSchemaAttributeType> Attributes, const FString& UserPoolId)
{
    UAddCustomAttributes_Async* Node = NewObject<UAddCustomAttributes_Async>();
    Node->Var_Attributes = Attributes;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UAddCustomAttributes_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AddCustomAttributesRequest AddCustomAttributesRequest;
    AddCustomAttributesRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    for (FSchemaAttributeType Attribute : Var_Attributes)
    {
        AddCustomAttributesRequest.AddCustomAttributes(Attribute.ToSchemaAttributeType());
    }
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AddCustomAttributesRequest&, const Aws::CognitoIdentityProvider::Model::AddCustomAttributesOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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
    CognitoObject->Var_CognitoIPClient->AddCustomAttributesAsync(AddCustomAttributesRequest, AsyncCallback);
    
}

void UAddCustomAttributes_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(Error);
}
