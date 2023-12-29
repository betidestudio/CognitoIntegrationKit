
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "SetLogDeliveryConfiguration_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSetLogDeliveryConfigurationAsyncOutputPin, FLogDeliveryConfigurationType, LogDeliveryConfiguration, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API USetLogDeliveryConfiguration_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static USetLogDeliveryConfiguration_Async* SetLogDeliveryConfiguration_Async(TArray<FLogConfigurationType> LogConfigurations, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	TArray<FLogConfigurationType> Var_LogConfigurations;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FOnSetLogDeliveryConfigurationAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSetLogDeliveryConfigurationAsyncOutputPin OnFailure;
};
