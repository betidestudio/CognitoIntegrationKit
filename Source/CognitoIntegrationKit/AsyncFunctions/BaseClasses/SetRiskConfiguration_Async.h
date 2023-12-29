
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "SetRiskConfiguration_Async.generated.h"

USTRUCT(BlueprintType)
struct FSetRiskConfigurationRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FAccountTakeoverRiskConfigurationType AccountTakeoverRiskConfiguration;

	UPROPERTY(BlueprintReadWrite)
	FCompromisedCredentialsRiskConfigurationType CompromisedCredentialsRiskConfiguration;

	UPROPERTY(BlueprintReadWrite)
	FRiskExceptionConfigurationType RiskExceptionConfiguration;

	UPROPERTY(BlueprintReadWrite)
	FString ClientId;

	UPROPERTY(BlueprintReadWrite)
	FString UserPoolId;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSetRiskConfigurationResult, FRiskConfigurationType, Result, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API USetRiskConfiguration_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static USetRiskConfiguration_Async* SetRiskConfiguration_Async(FSetRiskConfigurationRequest Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FSetRiskConfigurationRequest Var_Request;

	UPROPERTY(BlueprintAssignable)
	FSetRiskConfigurationResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FSetRiskConfigurationResult OnFailure;

};
