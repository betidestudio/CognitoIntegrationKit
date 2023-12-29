
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminGetDevice_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAdminGetDeviceResult,FDeviceType,DeviceType,FCognitoError,Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminGetDevice_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminGetDevice_Async* AdminGetDevice_Async(FString DeviceKey, FString Username, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FAdminGetDeviceResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminGetDeviceResult OnFailure;

	FString Var_DeviceKey;
	FString Var_Username;
	FString Var_UserPoolId;

};
