
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "SetUICustomization_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSetUICustomizationDelegate, FUICustomizationType, UICustomization, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API USetUICustomization_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static USetUICustomization_Async* SetUICustomization_Async(FString ClientId, FString CSS, FString UserPoolId, TArray<uint8> Image);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	TArray<uint8> Var_Image;
	FString Var_ClientId;
	FString Var_CSS;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FSetUICustomizationDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FSetUICustomizationDelegate OnFailure;
};
