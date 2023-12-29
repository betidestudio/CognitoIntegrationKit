
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EmailMessage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EmailSubject;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SMSMessage;
};

USTRUCT(BlueprintType)
struct FAdminCreateUserConfig
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool AllowAdminCreateUserOnly;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FInviteMessageTemplate InviteMessageTemplate;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 UnusedAccountValidityDays;

    
};

USTRUCT(BlueprintType)
struct FDeviceConfiguration
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool ChallengeRequiredOnNewDevice;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool DeviceOnlyRememberedOnUserPrompt;
};

USTRUCT(BlueprintType)
struct FEmailConfiguration
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ConfigurationSet;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString EmailSendingAccount;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString From;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ReplyToEmailAddress;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString SourceArn;
};


USTRUCT(BlueprintType)
struct FUpdateUserPoolRequest1
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAccountRecoverySettingType AccountRecoverySetting;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAdminCreateUserConfig AdminCreateUserConfig;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> AutoVerifiedAttributes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DeletionProtection;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FDeviceConfiguration DeviceConfiguration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FEmailConfiguration EmailConfiguration;

    // Add properties for all other nested structs defined

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString UserPoolId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
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
