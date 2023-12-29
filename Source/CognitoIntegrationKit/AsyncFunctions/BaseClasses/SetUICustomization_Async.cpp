
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "SetUICustomization_Async.h"

#include "aws/cognito-idp/model/SetUICustomizationRequest.h"

USetUICustomization_Async* USetUICustomization_Async::SetUICustomization_Async(FString ClientId, FString CSS, FString UserPoolId, TArray<uint8> Image)
{
    USetUICustomization_Async* Node = NewObject<USetUICustomization_Async>();
    Node->Var_ClientId = ClientId;
    Node->Var_CSS = CSS;
    Node->Var_UserPoolId = UserPoolId;
    Node->Var_Image = Image;
    return Node;
}

void USetUICustomization_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::SetUICustomizationRequest SetUICustomizationRequest;
    SetUICustomizationRequest.SetClientId(TCHAR_TO_UTF8(*Var_ClientId));
    SetUICustomizationRequest.SetCSS(TCHAR_TO_UTF8(*Var_CSS));
    SetUICustomizationRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    SetUICustomizationRequest.SetImageFile(Aws::Utils::ByteBuffer(Var_Image.GetData(), Var_Image.Num()));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SetUICustomizationRequest&, const Aws::CognitoIdentityProvider::Model::SetUICustomizationOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetUICustomization(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FUICustomizationType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->SetUICustomizationAsync(SetUICustomizationRequest, AsyncCallback);
}

void USetUICustomization_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FUICustomizationType(), Error);
}
