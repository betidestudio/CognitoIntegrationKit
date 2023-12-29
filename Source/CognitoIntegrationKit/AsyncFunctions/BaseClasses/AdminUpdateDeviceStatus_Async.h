
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminUpdateDeviceStatus_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdminUpdateDeviceStatusAsyncOutputPin, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminUpdateDeviceStatus_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminUpdateDeviceStatus_Async* AdminUpdateDeviceStatus_Async(FString DeviceKey, TEnumAsByte<EDeviceRememberedStatus> DeviceRememberedStatus, FString UserPoolId, FString Username);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FOnAdminUpdateDeviceStatusAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAdminUpdateDeviceStatusAsyncOutputPin OnFailure;

	FString Var_DeviceKey;
	TEnumAsByte<EDeviceRememberedStatus> Var_DeviceRememberedStatus;
	FString Var_UserPoolId;
	FString Var_Username;

};
