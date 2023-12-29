
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminResetUserPassword_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdminResetUserPasswordDelegate, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminResetUserPassword_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminResetUserPassword_Async* AdminResetUserPassword_Async(TMap<FString, FString> ClientMetaData, FString Username, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	TMap<FString, FString> ClientMetaData;
	FString Var_Username;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FAdminResetUserPasswordDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminResetUserPasswordDelegate OnFailure;
};
