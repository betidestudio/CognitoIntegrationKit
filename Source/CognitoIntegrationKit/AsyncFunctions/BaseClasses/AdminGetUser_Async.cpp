
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "AdminGetUser_Async.h"

#include "aws/cognito-idp/model/AdminGetUserRequest.h"

UAdminGetUser_Async* UAdminGetUser_Async::AdminGetUser_Async(FString UserPoolId, FString Username)
{
    UAdminGetUser_Async* Node = NewObject<UAdminGetUser_Async>();
    Node->Var_UserPoolId = UserPoolId;
    Node->Var_Username = Username;
    return Node;
}

void UAdminGetUser_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::AdminGetUserRequest AdminGetUserRequest;
    AdminGetUserRequest.WithUserPoolId(TCHAR_TO_UTF8(*Var_UserPoolId));
    AdminGetUserRequest.WithUsername(TCHAR_TO_UTF8(*Var_Username));

    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::AdminGetUserRequest&, const Aws::CognitoIdentityProvider::Model::AdminGetUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                FAdminGetUserResponse AdminGetUserResponse;
                AdminGetUserResponse.bEnabled = outcome.GetResult().GetEnabled();
                AdminGetUserResponse.PreferredMfaSetting = outcome.GetResult().GetPreferredMfaSetting().c_str();
                //AdminGetUserResponse.UserCreateDate = outcome.GetResult().GetUserCreateDate();
                //AdminGetUserResponse.UserLastModifiedDate = outcome.GetResult().GetUserLastModifiedDate();
                AdminGetUserResponse.Username = outcome.GetResult().GetUsername().c_str();
                AdminGetUserResponse.UserStatus = static_cast<EUserStatusType>(outcome.GetResult().GetUserStatus());
                TArray<FAttributeType> UserAttributes;
                for (auto Attribute : outcome.GetResult().GetUserAttributes())
                {
                    FAttributeType AttributeType;
                    AttributeType.Name = Attribute.GetName().c_str();
                    AttributeType.Value = Attribute.GetValue().c_str();
                    UserAttributes.Add(AttributeType);
                }
                AdminGetUserResponse.UserAttributes = UserAttributes;
                TArray<FMFAOptionType> MFAOptions;
                for (auto MFAOption : outcome.GetResult().GetMFAOptions())
                {
                    FMFAOptionType MFAOptionType;
                    MFAOptionType.DeliveryMedium = static_cast<EDeliveryMediumType>(MFAOption.GetDeliveryMedium());
                    MFAOptionType.AttributeName = MFAOption.GetAttributeName().c_str();
                    MFAOptions.Add(MFAOptionType);
                }
                AdminGetUserResponse.MFAOptions = MFAOptions;
                TArray<FString> UserMFASettingList;
                for (auto UserMFASetting : outcome.GetResult().GetUserMFASettingList())
                {
                    UserMFASettingList.Add(UserMFASetting.c_str());
                }
                AdminGetUserResponse.UserMFASettingList = UserMFASettingList;
                OnSuccess.Broadcast(AdminGetUserResponse, FCognitoError());
                
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(FAdminGetUserResponse(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->AdminGetUserAsync(AdminGetUserRequest, AsyncCallback);
}

void UAdminGetUser_Async::ExecuteFailure(FCognitoError Error)
{
    
}
