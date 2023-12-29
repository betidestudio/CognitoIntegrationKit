
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DescribeIdentityProvider_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDescribeIdentityProviderDelegate, FIdentityProviderType, IdentityProvider, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDescribeIdentityProvider_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDescribeIdentityProvider_Async* DescribeIdentityProvider_Async(FString ProviderName, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_ProviderName;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FDescribeIdentityProviderDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDescribeIdentityProviderDelegate OnFailure;

};
