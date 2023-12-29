
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ChangePassword_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FChangePasswordDelegate, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UChangePassword_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UChangePassword_Async* ChangePassword_Async(FString AccessToken, FString PreviousPassword, FString ProposedPassword);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;
	FString Var_PreviousPassword;
	FString Var_ProposedPassword;

	UPROPERTY(BlueprintAssignable)
	FChangePasswordDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FChangePasswordDelegate OnFailure;

};
