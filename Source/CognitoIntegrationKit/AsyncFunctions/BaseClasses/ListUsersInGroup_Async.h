
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ListUsersInGroup_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListUsersInGroupAsyncOutputPin, FString, NextToken, TArray<FUserType>, Users, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UListUsersInGroup_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UListUsersInGroup_Async* ListUsersInGroup_Async(int32 Limit, FString GroupName, FString UserPoolId, FString NextToken);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_GroupName;
	int32 Var_Limit;
	FString Var_NextToken;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FListUsersInGroupAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListUsersInGroupAsyncOutputPin OnFailure;
};
