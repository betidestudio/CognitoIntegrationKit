
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ListGroups_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListGroupsDelegate, FString, NextToken, TArray<FGroupType>, Groups, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UListGroups_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UListGroups_Async* ListGroups_Async(int32 Limit, FString NextToken, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_NextToken;
	int32 Var_Limit;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FListGroupsDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListGroupsDelegate OnFailure;

};
