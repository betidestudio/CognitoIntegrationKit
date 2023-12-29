
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminEnableUser_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdminEnableUserAsync, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminEnableUser_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminEnableUser_Async* AdminEnableUser_Async(FString Username, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FOnAdminEnableUserAsync OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAdminEnableUserAsync OnFailure;

	FString Var_Username;
	FString Var_UserPoolId;

};
