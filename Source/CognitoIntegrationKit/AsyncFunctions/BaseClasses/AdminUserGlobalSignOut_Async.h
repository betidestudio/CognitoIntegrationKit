
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminUserGlobalSignOut_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdminUserGlobalSignOutDelegate, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminUserGlobalSignOut_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminUserGlobalSignOut_Async* AdminUserGlobalSignOut_Async(FString UserPoolId, FString Username);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_UserPoolId;
	FString Var_Username;

	UPROPERTY(BlueprintAssignable)
	FAdminUserGlobalSignOutDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminUserGlobalSignOutDelegate OnFailure;

};
