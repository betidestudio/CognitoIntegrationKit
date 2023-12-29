
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ListResourceServers_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListResourceServersDelegate, FString, NextToken, TArray<FResourceServerType>, ResourceServers, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UListResourceServers_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UListResourceServers_Async* ListResourceServers_Async(int32 MaxResults, FString NextToken, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	int32 Var_MaxResults;
	FString Var_NextToken;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FListResourceServersDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListResourceServersDelegate OnFailure;
};
