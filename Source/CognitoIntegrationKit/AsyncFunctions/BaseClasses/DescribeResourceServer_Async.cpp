
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "DescribeResourceServer_Async.h"

#include "aws/cognito-idp/model/DescribeResourceServerRequest.h"

UDescribeResourceServer_Async* UDescribeResourceServer_Async::DescribeResourceServer_Async(FString UserPoolId, FString Identifer)
{
    UDescribeResourceServer_Async* Node = NewObject<UDescribeResourceServer_Async>();
    Node->Var_Identifer = Identifer;
    Node->Var_UserPoolId = UserPoolId;
    return Node;
}

void UDescribeResourceServer_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::DescribeResourceServerRequest DescribeResourceServerRequest;
    DescribeResourceServerRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    DescribeResourceServerRequest.SetIdentifier(TCHAR_TO_UTF8(*Var_Identifer));
    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::DescribeResourceServerRequest&, const Aws::CognitoIdentityProvider::Model::DescribeResourceServerOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                OnSuccess.Broadcast(FResourceServerType(outcome.GetResult().GetResourceServer()), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FResourceServerType(),Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->DescribeResourceServerAsync(DescribeResourceServerRequest, AsyncCallback);
}

void UDescribeResourceServer_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FResourceServerType(),Error);
}
