
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DeleteUserPool_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleteUserPoolDelegate, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UDeleteUserPool_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDeleteUserPool_Async* DeleteUserPool_Async(FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FDeleteUserPoolDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDeleteUserPoolDelegate OnFailure;
};
