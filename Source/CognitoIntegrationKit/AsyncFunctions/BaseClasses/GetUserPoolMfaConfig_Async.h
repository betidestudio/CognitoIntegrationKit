
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "GetUserPoolMfaConfig_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FGetUserPoolMfaConfigDelegate, int32, MFAOptions, FSmsMfaConfigType, SmsConfig, FSoftwareTokenMfaConfigType, SoftwareTokenConfig, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UGetUserPoolMfaConfig_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UGetUserPoolMfaConfig_Async* GetUserPoolMfaConfig_Async(FString UserPoolID);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_UserPoolID;

	UPROPERTY(BlueprintAssignable)
	FGetUserPoolMfaConfigDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetUserPoolMfaConfigDelegate OnFailure;

};
