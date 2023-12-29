
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminCreateUser_Async.h"

#include "aws/cognito-idp/model/AdminCreateUserRequest.h"

UAdminCreateUser_Async* UAdminCreateUser_Async::AdminCreateUser_Async(FAdminCreateUserReq AdminCreateUserReq)
{
    UAdminCreateUser_Async* Node = NewObject<UAdminCreateUser_Async>();
    Node->Var_AdminCreateUserReq = AdminCreateUserReq;
    return Node;
}

void UAdminCreateUser_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminCreateUserRequest CreateUserRequest;
    CreateUserRequest.SetUsername(TCHAR_TO_UTF8(*Var_AdminCreateUserReq.Username));
    CreateUserRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_AdminCreateUserReq.UserPoolId));
    CreateUserRequest.SetForceAliasCreation(Var_AdminCreateUserReq.ForceAliasCreation);
    CreateUserRequest.SetTemporaryPassword(TCHAR_TO_UTF8(*Var_AdminCreateUserReq.TemporaryPassword));
    for (FAttributeType Attribute : Var_AdminCreateUserReq.UserAttributes)
    {
        CreateUserRequest.AddUserAttributes(Attribute.ToAttributeType());
    }
    for (FAttributeType Attribute : Var_AdminCreateUserReq.ValidationData)
    {
        CreateUserRequest.AddValidationData(Attribute.ToAttributeType());
    }
    for (TEnumAsByte<EDeliveryMediumType> DeliveryMedium : Var_AdminCreateUserReq.DesiredDeliveryMediums)
    {
        Aws::CognitoIdentityProvider::Model::DeliveryMediumType DeliveryMediumType = static_cast< Aws::CognitoIdentityProvider::Model::DeliveryMediumType>(DeliveryMedium.GetValue());
        CreateUserRequest.AddDesiredDeliveryMediums(DeliveryMediumType);
    }
    for (auto& it : Var_AdminCreateUserReq.ClientMetaData)
    {
        CreateUserRequest.AddClientMetadata(TCHAR_TO_UTF8(*it.Key), TCHAR_TO_UTF8(*it.Value));
    }
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminCreateUserRequest&, const Aws::CognitoIdentityProvider::Model::AdminCreateUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                FUserType User(outcome.GetResult().GetUser());
                OnSuccess.Broadcast(User, FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FUserType(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->AdminCreateUserAsync(CreateUserRequest, AsyncCallback);
}

void UAdminCreateUser_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(FUserType(), Error);
}
