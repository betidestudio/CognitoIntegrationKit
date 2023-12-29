
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminListGroupsForUser_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAdminListGroupsForUserResponse, const TArray<FGroupType>&, Groups, const FString&, NextToken, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminListGroupsForUser_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminListGroupsForUser_Async* AdminListGroupsForUser_Async();

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	int32 Var_Limit;
	FString Var_NextToken;
	FString Var_Username;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FOnAdminListGroupsForUserResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAdminListGroupsForUserResponse OnFailure;
};
