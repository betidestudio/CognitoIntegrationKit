
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminDeleteUser_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdminDeleteUserAsync, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminDeleteUser_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit", DisplayName = "Admin Delete User")
	static UAdminDeleteUser_Async* AdminDeleteUser_Async(FString UserPoolId, FString Username);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_UserPoolId;
	FString Var_Username;

	UPROPERTY(BlueprintAssignable)
	FOnAdminDeleteUserAsync OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAdminDeleteUserAsync OnFailure;

};
