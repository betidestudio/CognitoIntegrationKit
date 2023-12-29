
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminDisableUser_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdminDisableUserAsync, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminDisableUser_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminDisableUser_Async* AdminDisableUser_Async(FString UserPoolId, FString Username);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_UserPoolId;
	FString Var_Username;

	UPROPERTY(BlueprintAssignable)
	FOnAdminDisableUserAsync OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAdminDisableUserAsync OnFailure;

};
