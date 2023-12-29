
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminListDevices_Async.generated.h"

USTRUCT(BlueprintType)
struct FAdminListDevicesResult
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "CognitoIntegrationKit")
	TArray<FDeviceType> Devices;
	
	UPROPERTY(BlueprintReadWrite)
	FString PaginationToken;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAdminListDevicesAsyncCompleted, FAdminListDevicesResult, Result, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminListDevices_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminListDevices_Async* AdminListDevices_Async(int32 Limit, FString PaginationToken, FString Username, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	int32 Var_Limit;
	FString Var_PaginationToken;
	FString Var_Username;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FOnAdminListDevicesAsyncCompleted OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAdminListDevicesAsyncCompleted OnFailure;
	

};
