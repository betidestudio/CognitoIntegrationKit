
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "CreateUserImportJob_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateUserImportJobDelegate,FUserImportJobType,UserImportJob,FCognitoError,Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UCreateUserImportJob_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UCreateUserImportJob_Async* CreateUserImportJob_Async(FString UserPoolId, FString JobName, FString CloudWatchLogsRoleArn);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FCreateUserImportJobDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateUserImportJobDelegate OnFailure;

	FString Var_CloudWatchLogsRoleArn;
	FString Var_JobName;
	FString Var_UserPoolId;

};
