
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "GetUserAttributeVerificationCode_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetUserAttributeVerificationCodeDelegate, FCodeDeliveryDetailsType, CodeDeliveryDetails, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UGetUserAttributeVerificationCode_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UGetUserAttributeVerificationCode_Async* GetUserAttributeVerificationCode_Async(FString AccessToken, FString AttributeName, TMap<FString,FString> ClientMetadata);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;
	FString Var_AttributeName;
	TMap<FString,FString> Var_ClientMetadata;

	UPROPERTY(BlueprintAssignable)
	FGetUserAttributeVerificationCodeDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetUserAttributeVerificationCodeDelegate OnFailure;
	
};
