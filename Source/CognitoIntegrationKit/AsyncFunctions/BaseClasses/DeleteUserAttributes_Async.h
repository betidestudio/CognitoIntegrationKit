
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DeleteUserAttributes_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleteUserAttributesDelegate, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDeleteUserAttributes_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDeleteUserAttributes_Async* DeleteUserAttributes_Async(FString AccessToken, TArray<FString> UserAttributeNames);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;
	TArray<FString> Var_UserAttributeNames;
	
	UPROPERTY(BlueprintAssignable)
	FDeleteUserAttributesDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDeleteUserAttributesDelegate OnFailure;
};
