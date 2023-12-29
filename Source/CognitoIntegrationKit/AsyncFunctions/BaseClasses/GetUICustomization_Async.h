
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "GetUICustomization_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetUICustomizationDelegate, FCognitoError, Error, FUICustomizationType, UICustomization);

UCLASS()
class COGNITOINTEGRATIONKIT_API UGetUICustomization_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UGetUICustomization_Async* GetUICustomization_Async(FString ClientId, FString UsePoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FGetUICustomizationDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetUICustomizationDelegate OnFailure;

	FString Var_ClientId;
	FString Var_UsePoolId;
};
