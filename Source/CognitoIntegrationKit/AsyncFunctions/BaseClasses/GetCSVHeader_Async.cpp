
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "GetCSVHeader_Async.h"

#include "aws/cognito-idp/model/GetCSVHeaderRequest.h"

UGetCSVHeader_Async* UGetCSVHeader_Async::GetCSVHeader_Async(FString UserPoolID)
{
    UGetCSVHeader_Async* Node = NewObject<UGetCSVHeader_Async>();
    Node->Var_UserPoolID = UserPoolID;
    return Node;
}

void UGetCSVHeader_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::GetCSVHeaderRequest GetCSVHeaderRequest;
    GetCSVHeaderRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolID));
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetCSVHeaderRequest&, const Aws::CognitoIdentityProvider::Model::GetCSVHeaderOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FString> CSVHeader;
                for (auto& Header : outcome.GetResult().GetCSVHeader())
                {
                    CSVHeader.Add(FString(Header.c_str()));
                }
                OnSuccess.Broadcast(CSVHeader, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(TArray<FString>(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->GetCSVHeaderAsync(GetCSVHeaderRequest, AsyncCallback);
}

void UGetCSVHeader_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(TArray<FString>(), Error);
}
