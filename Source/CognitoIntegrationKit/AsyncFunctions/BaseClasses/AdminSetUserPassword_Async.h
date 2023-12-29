
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminSetUserPassword_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdminSetUserPasswordAsyncOutputPin, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminSetUserPassword_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminSetUserPassword_Async* AdminSetUserPassword_Async(FString Password, bool Permanent, FString Username, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_Password;
	bool bVar_Permanent;
	FString Var_Username;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FAdminSetUserPasswordAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminSetUserPasswordAsyncOutputPin OnFailure;
};
