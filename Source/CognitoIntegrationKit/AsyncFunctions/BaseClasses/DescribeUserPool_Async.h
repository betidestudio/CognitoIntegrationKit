
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DescribeUserPool_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDescribeUserPoolSuccess, FUserPoolType, UserPool, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDescribeUserPool_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDescribeUserPool_Async* DescribeUserPool_Async(FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FDescribeUserPoolSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDescribeUserPoolSuccess OnFailure;

	FString Var_UserPoolId;

};
