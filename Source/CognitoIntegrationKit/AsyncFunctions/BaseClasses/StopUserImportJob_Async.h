
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "StopUserImportJob_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FStopUserImportJobDelegate,FUserImportJobType,UserImportJob,FCognitoError,Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UStopUserImportJob_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UStopUserImportJob_Async* StopUserImportJob_Async(FString JobID, FString UserPoolID);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;
	
	FString Var_JobID;
	FString Var_UserPoolID;

	UPROPERTY(BlueprintAssignable)
	FStopUserImportJobDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FStopUserImportJobDelegate OnFailure;

};
