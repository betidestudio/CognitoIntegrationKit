
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ListDevices_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListDevicesResponse,TArray<FDeviceType>,Devices,FString,PaginationToken,FCognitoError,Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UListDevices_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UListDevices_Async* ListDevices_Async(FString AccessToken, int32 Limit, FString PaginationToken);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;
	int32 Var_Limit;
	FString Var_PaginationToken;

	UPROPERTY(BlueprintAssignable)
	FListDevicesResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListDevicesResponse OnFailure;

};
