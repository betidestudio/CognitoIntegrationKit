
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DeleteResourceServer_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleteResourceServerDelegate, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDeleteResourceServer_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDeleteResourceServer_Async* DeleteResourceServer_Async(FString UserPoolId, FString Identifier);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_Identifer;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FDeleteResourceServerDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDeleteResourceServerDelegate OnFailure;
	
};
