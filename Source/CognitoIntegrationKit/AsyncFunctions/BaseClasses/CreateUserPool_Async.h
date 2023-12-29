
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "CreateUserPool_Async.generated.h"


USTRUCT(BlueprintType)
struct FCreateUserPoolRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FAccountRecoverySettingType AccountRecoverySetting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FAdminCreateUserConfigType AdminCreateUserConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	TArray<FString> AliasAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	TArray<FString> AutoVerifiedAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FDeviceConfigurationType DeviceConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString DelectionProtection;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FEmailConfigurationType EmailConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString EmailVerificationMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString EmailVerificationSubject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FLambdaConfigType LambdaConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString MfaConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FUserPoolPolicyType Policies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString PoolName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
 	TArray<FSchemaAttributeType> Schema;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString SmsAuthenticationMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FSmsConfigurationType SmsConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FUserAttributeUpdateSettingsType UserAttribute;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	TArray<FString> UsernameAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FUsernameConfigurationType UsernameConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FUserPoolAddOnsType	UserPoolAddOns;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Provider")
	FVerificationMessageTemplateType VerificationMessageTemplate;
};
/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateUserPoolResult, FUserPoolType, UserPool, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UCreateUserPool_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UCreateUserPool_Async* CreateUserPool_Async(FCreateUserPoolRequest Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FCreateUserPoolRequest Var_Request;

	UPROPERTY(BlueprintAssignable)
	FCreateUserPoolResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateUserPoolResult OnFailure;

};
