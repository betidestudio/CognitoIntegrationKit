
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DescribeResourceServer_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDescribeResourceServerDelegate, FResourceServerType, Resource, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDescribeResourceServer_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDescribeResourceServer_Async* DescribeResourceServer_Async(FString UserPoolId, FString Identifer);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_Identifer;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FDescribeResourceServerDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDescribeResourceServerDelegate OnFailure;

};
