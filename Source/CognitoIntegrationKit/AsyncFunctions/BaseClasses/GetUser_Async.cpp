
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "GetUser_Async.h"

#include "aws/cognito-idp/model/GetUserRequest.h"

UGetUser_Async* UGetUser_Async::GetUser_Async(FString AccessToken)
{
    UGetUser_Async* Node = NewObject<UGetUser_Async>();
    Node->Var_AccessToken = AccessToken;
    return Node;
}

void UGetUser_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::GetUserRequest GetUserRequest;
    GetUserRequest.SetAccessToken(TCHAR_TO_UTF8(*Var_AccessToken));

    
    auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::GetUserRequest&, const Aws::CognitoIdentityProvider::Model::GetUserOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
    {
        AsyncTask(ENamedThreads::GameThread, [outcome, this]()
        {
            if (outcome.IsSuccess())
            {
                TArray<FMFAOptionType> MFAOptions;
                for (auto MFAOption : outcome.GetResult().GetMFAOptions())
                {
                    FMFAOptionType MFAOptionType;
                    MFAOptionType.AttributeName = FString(MFAOption.GetAttributeName().c_str());
                    MFAOptionType.DeliveryMedium = static_cast<EDeliveryMediumType>(MFAOption.GetDeliveryMedium());
                    MFAOptions.Add(MFAOptionType);
                }
                TArray<FAttributeType> UserAttributes;
                for (auto Attribute : outcome.GetResult().GetUserAttributes())
                {
                    FAttributeType AttributeType;
                    AttributeType.Name = FString(Attribute.GetName().c_str());
                    AttributeType.Value = FString(Attribute.GetValue().c_str());
                    UserAttributes.Add(AttributeType);
                }
                TArray<FString> UserMFASettingList;
                for (auto UserMFASetting : outcome.GetResult().GetUserMFASettingList())
                {
                    UserMFASettingList.Add(FString(UserMFASetting.c_str()));
                }
                OnSuccess.Broadcast(MFAOptions, FString(outcome.GetResult().GetPreferredMfaSetting().c_str()),UserAttributes, UserMFASettingList, FString(outcome.GetResult().GetUsername().c_str()), FCognitoError());
            }
            else
            {
                FCognitoError Error;
                Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
                Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
                Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
                Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
                Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
                OnFailure.Broadcast(TArray<FMFAOptionType>(), FString(), TArray<FAttributeType>(), TArray<FString>(), FString(), Error);
            }
            SetReadyToDestroy();
        });
    };
    CognitoObject->Var_CognitoIPClient->GetUserAsync(GetUserRequest, AsyncCallback);
}

void UGetUser_Async::ExecuteFailure(FCognitoError Error)
{
    OnFailure.Broadcast(TArray<FMFAOptionType>(), FString(), TArray<FAttributeType>(), TArray<FString>(), FString(), Error);
}
