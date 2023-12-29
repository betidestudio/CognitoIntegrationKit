
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DescribeUserImportJob_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDescribeUserImportJobDelegate, FUserImportJobType, UserImportJob, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDescribeUserImportJob_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDescribeUserImportJob_Async* DescribeUserImportJob_Async(FString JobId, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_JobId;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FDescribeUserImportJobDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDescribeUserImportJobDelegate OnFailure;

};
