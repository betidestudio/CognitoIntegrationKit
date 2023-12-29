
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "UpdateUserPoolDomain_Async.h"
#include "aws/cognito-idp/model/UpdateUserPoolDomainRequest.h"

UUpdateUserPoolDomain_Async* UUpdateUserPoolDomain_Async::UpdateUserPoolDomain_Async(UObject* WorldContextObject, FString Domain, FString UserPoolID, FString CertificateArn)
{
    UUpdateUserPoolDomain_Async* Node = NewObject<UUpdateUserPoolDomain_Async>();
    Node->Var_Domain = Domain;
    Node->Var_UserPoolID = UserPoolID;
    Node->Var_CustomDomainConfig_CertificateArn = CertificateArn;
    return Node;
}

void UUpdateUserPoolDomain_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::UpdateUserPoolDomainRequest UpdateUserPoolDomainRequest;
    UpdateUserPoolDomainRequest.SetDomain(TCHAR_TO_UTF8(*Var_Domain));
    UpdateUserPoolDomainRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolID));
    Aws::CognitoIdentityProvider::Model::CustomDomainConfigType CustomDomainConfig;
    CustomDomainConfig.SetCertificateArn(TCHAR_TO_UTF8(*Var_CustomDomainConfig_CertificateArn));
    UpdateUserPoolDomainRequest.SetCustomDomainConfig(CustomDomainConfig);

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolDomainRequest&, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolDomainOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(outcome.GetResult().GetCloudFrontDomain().c_str(), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
            OnFailure.Broadcast("",Error);
            }
        });
    };

    CognitoObject->Var_CognitoIPClient->UpdateUserPoolDomainAsync(UpdateUserPoolDomainRequest, AsyncCallback);
}

void UUpdateUserPoolDomain_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast("", Error);
}
