
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "UpdateDeviceStatus_Async.generated.h"


USTRUCT(BlueprintType)
struct FUpdateDeviceStatusReq
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString AccessToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString DeviceToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TEnumAsByte<EDeviceRememberedStatus> DeviceRememberedStatus = EDeviceRememberedStatus::NOT_SET29;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateDeviceStatusResult, const FCognitoError&, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UUpdateDeviceStatus_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UUpdateDeviceStatus_Async* UpdateDeviceStatus_Async(FUpdateDeviceStatusReq UpdateDeviceStatusReq);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FUpdateDeviceStatusReq Var_UpdateDeviceStatusReq;
	
	UPROPERTY(BlueprintAssignable)
	FUpdateDeviceStatusResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FUpdateDeviceStatusResult OnFailure;
};
