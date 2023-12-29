
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "GetLogDeliveryConfiguration_Async.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetLogDeliveryConfigurationDelegate, FLogDeliveryConfigurationType, LogDeliveryConfiguration, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UGetLogDeliveryConfiguration_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UGetLogDeliveryConfiguration_Async* GetLogDeliveryConfiguration_Async(FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FGetLogDeliveryConfigurationDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetLogDeliveryConfigurationDelegate OnFailure;

};
