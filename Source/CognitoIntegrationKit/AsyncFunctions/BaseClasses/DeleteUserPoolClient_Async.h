
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DeleteUserPoolClient_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleteUserPoolClientDelegate, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDeleteUserPoolClient_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDeleteUserPoolClient_Async* DeleteUserPoolClient_Async(FString ClientId, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_ClientId;
	FString Var_UserPoolId;
	UPROPERTY(BlueprintAssignable)
	FDeleteUserPoolClientDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDeleteUserPoolClientDelegate OnFailure;

};
