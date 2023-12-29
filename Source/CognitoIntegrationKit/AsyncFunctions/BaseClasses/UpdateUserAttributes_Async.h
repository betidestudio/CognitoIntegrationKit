
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "UpdateUserAttributes_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateUserAttributesAsyncOutputPin, TArray<FCodeDeliveryDetailsType>, CodeDeliveryDetails, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UUpdateUserAttributes_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UUpdateUserAttributes_Async* UpdateUserAttributes_Async(FString AccessToken, TMap<FString, FString> ClientMetadata, TArray<FAttributeType> UserAttributes);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;
	TMap<FString, FString> Var_ClientMetadata;
	TArray<FAttributeType> Var_UserAttributes;

	UPROPERTY(BlueprintAssignable)
	FUpdateUserAttributesAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FUpdateUserAttributesAsyncOutputPin OnFailure;

};
