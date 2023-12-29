
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ListUserImportJobs_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListUserImportJobsDelegate, FString, PaginationToken, TArray<FUserImportJobType>, UserImportJobs, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UListUserImportJobs_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UListUserImportJobs_Async* ListUserImportJobs_Async(int32 MaxResults, FString PaginationToken, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	int32 Var_MaxResults;
	FString Var_PaginationToken;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FListUserImportJobsDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListUserImportJobsDelegate OnFailure;

};
