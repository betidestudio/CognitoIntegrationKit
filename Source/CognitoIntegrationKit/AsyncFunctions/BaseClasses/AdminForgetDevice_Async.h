
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminForgetDevice_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdminForgetDeviceDelegate, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminForgetDevice_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminForgetDevice_Async* AdminForgetDevice_Async(FString Username, FString DeviceKey, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FAdminForgetDeviceDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminForgetDeviceDelegate OnFailure;

	FString Var_Username;
	FString Var_DeviceKey;
	FString Var_UserPoolId;
};
