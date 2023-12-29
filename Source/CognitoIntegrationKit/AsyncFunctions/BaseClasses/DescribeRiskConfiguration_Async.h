
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DescribeRiskConfiguration_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDescribeRiskConfigurationDelegate, FRiskConfigurationType, RiskConfiguration, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDescribeRiskConfiguration_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDescribeRiskConfiguration_Async* DescribeRiskConfiguration_Async(FString ClientId, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_ClientId;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FDescribeRiskConfigurationDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDescribeRiskConfigurationDelegate OnFailure;

};
