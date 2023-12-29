
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "GetSigningCertificate_Async.h"

#include "aws/cognito-idp/model/GetSigningCertificateRequest.h"

UGetSigningCertificate_Async* UGetSigningCertificate_Async::GetSigningCertificate_Async(FString UserPoolId)
{
    UGetSigningCertificate_Async* Node = NewObject<UGetSigningCertificate_Async>();
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UGetSigningCertificate_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::GetSigningCertificateRequest GetSigningCertificateRequest;
    GetSigningCertificateRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetSigningCertificateRequest&, const Aws::CognitoIdentityProvider::Model::GetSigningCertificateOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FString(outcome.GetResult().GetCertificate().c_str()), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FString(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->GetSigningCertificateAsync(GetSigningCertificateRequest, AsyncCallback);
}

void UGetSigningCertificate_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FString(), Error);
}
