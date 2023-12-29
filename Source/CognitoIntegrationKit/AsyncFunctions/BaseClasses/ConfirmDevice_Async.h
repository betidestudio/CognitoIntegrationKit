
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ConfirmDevice_Async.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FConfirmDeviceDelegate, bool ,bUserConfirmationNecessary,FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UConfirmDevice_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	/**
	* Confirms tracking of the device. This API call is the call that begins device tracking.
	*/
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UConfirmDevice_Async* ConfirmDevice_Async(FString AccessToken, FString DeviceKey, FDeviceSecretVerifierConfigType DeviceSecretVerifierConfig, FString DeviceName);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;
	FString Var_DeviceKey;
	FDeviceSecretVerifierConfigType Var_DeviceSecretVerifierConfig;
	FString Var_DeviceName;

	UPROPERTY(BlueprintAssignable)
	FConfirmDeviceDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FConfirmDeviceDelegate OnFailure;

};
