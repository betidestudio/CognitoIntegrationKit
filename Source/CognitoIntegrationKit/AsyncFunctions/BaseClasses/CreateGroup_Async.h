
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "CreateGroup_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateGroupAsyncResponse,FGroupType,Result, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UCreateGroup_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UCreateGroup_Async* CreateGroup_Async(FString Description, FString GroupName, int32 Precedence, FString RoleArn, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FCreateGroupAsyncResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateGroupAsyncResponse OnFailure;

	FString Var_Description;
	FString Var_GroupName;
	int32 Var_Precedence;
	FString Var_RoleArn;
	FString Var_UserPoolId;

};
