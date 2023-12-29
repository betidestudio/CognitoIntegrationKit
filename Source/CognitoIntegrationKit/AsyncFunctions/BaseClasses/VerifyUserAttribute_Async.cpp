
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "VerifyUserAttribute_Async.h"

#include "aws/cognito-idp/model/VerifyUserAttributeRequest.h"

UVerifyUserAttribute_Async* UVerifyUserAttribute_Async::VerifyUserAttribute_Async(UObject* WorldContextObject, FString AttributeName, FString AccessToken, FString Code)
{
    UVerifyUserAttribute_Async* Node = NewObject<UVerifyUserAttribute_Async>();
    Node->Var_AttributeName = AttributeName;
    Node->Var_AccessToken = AccessToken;
    Node->Var_Code = Code;
    return Node;
}

void UVerifyUserAttribute_Async::Activate()
{
    FCognitoError Local_FailureResponse = FCognitoError();
    Super::Activate();
    TArray<UCIK_Object*> Objects;
    for (TObjectIterator<UCIK_Object> Itr; Itr; ++Itr)
    {
        Objects.Add(*Itr);
    }
    if(Objects[0])
    {
        if(Objects[0]->CognitoClientID.IsEmpty())
        {
            Local_FailureResponse.ErrorMessage = "Cognito Client ID is empty";
            OnFailure.Broadcast(Local_FailureResponse);
            SetReadyToDestroy();
        }
        else
        {
            ContinueProcess(Objects[0]);
        }
    }
    else
    {
        Local_FailureResponse.ErrorMessage = "No object found";
        OnFailure.Broadcast(Local_FailureResponse);
        SetReadyToDestroy();
    }
}

void UVerifyUserAttribute_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::VerifyUserAttributeRequest VerifyUserAttributeRequest;
    VerifyUserAttributeRequest.SetAttributeName(TCHAR_TO_UTF8(*Var_AttributeName));
    VerifyUserAttributeRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));
    VerifyUserAttributeRequest.SetCode(TCHAR_TO_UTF8(*Var_Code));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::VerifyUserAttributeRequest&, const Aws::CognitoIdentityProvider::Model::VerifyUserAttributeOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
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

    CognitoObject->Var_CognitoIPClient->VerifyUserAttributeAsync(VerifyUserAttributeRequest, AsyncCallback);

}
