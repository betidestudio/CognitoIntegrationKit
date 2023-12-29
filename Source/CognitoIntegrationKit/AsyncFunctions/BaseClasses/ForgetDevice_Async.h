
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ForgetDevice_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnForgetDeviceCompleted, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UForgetDevice_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UForgetDevice_Async* ForgetDevice_Async(FString AccessToken, FString DeviceKey);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;
	FString Var_DeviceKey;

	UPROPERTY(BlueprintAssignable)
	FOnForgetDeviceCompleted OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnForgetDeviceCompleted OnFailure;
};
