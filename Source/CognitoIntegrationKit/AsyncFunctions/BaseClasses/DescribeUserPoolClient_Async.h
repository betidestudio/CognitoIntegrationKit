
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DescribeUserPoolClient_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDescribeUserPoolClientDelegate, FUserPoolClientType, UserPoolClient, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDescribeUserPoolClient_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDescribeUserPoolClient_Async* DescribeUserPoolClient_Async(FString ClientId, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FDescribeUserPoolClientDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDescribeUserPoolClientDelegate OnFailure;

	FString Var_ClientId;
	FString Var_UserPoolId;

};
