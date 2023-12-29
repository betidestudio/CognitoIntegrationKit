
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UpdateUserPool_Async.generated.h"



USTRUCT(BlueprintType)
struct FInviteMessageTemplate
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString EmailMessage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString EmailSubject;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString SMSMessage;
};

USTRUCT(BlueprintType)
struct FAdminCreateUserConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    bool AllowAdminCreateUserOnly;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FInviteMessageTemplate InviteMessageTemplate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    int32 UnusedAccountValidityDays;

    
};

USTRUCT(BlueprintType)
struct FDeviceConfiguration
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    bool ChallengeRequiredOnNewDevice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    bool DeviceOnlyRememberedOnUserPrompt;
};

USTRUCT(BlueprintType)
struct FEmailConfiguration
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString ConfigurationSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString EmailSendingAccount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString From;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString ReplyToEmailAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString SourceArn;
};


USTRUCT(BlueprintType)
struct FUpdateUserPoolRequest1
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FAccountRecoverySettingType AccountRecoverySetting;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FAdminCreateUserConfig AdminCreateUserConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    TArray<FString> AutoVerifiedAttributes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString DeletionProtection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FDeviceConfiguration DeviceConfiguration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FEmailConfiguration EmailConfiguration;

    // Add properties for all other nested structs defined

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString UserPoolId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    TMap<FString, FString> UserPoolTags;
};


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateUserPoolSuccess, const FCognitoError&, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UUpdateUserPool_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Cogntio Identity Kit")
	static UUpdateUserPool_Async* UpdateUserPool_Async(UObject* WorldContextObject, FUpdateUserPoolRequest1 UpdateUserPoolRequest);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;
    virtual void ExecuteFailure(FCognitoError Error) override;
    
    FUpdateUserPoolRequest1 Var_UpdateUserPoolRequest;

    UPROPERTY(BlueprintAssignable)
    FUpdateUserPoolSuccess OnSuccess;

    UPROPERTY(BlueprintAssignable)
    FUpdateUserPoolSuccess OnFailure;

};
