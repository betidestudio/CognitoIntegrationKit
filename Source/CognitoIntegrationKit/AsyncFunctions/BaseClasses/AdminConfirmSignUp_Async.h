
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminConfirmSignUp_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdminConfirmSignUpResponse, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminConfirmSignUp_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit", DisplayName = "Admin Confirm Sign Up")
	static UAdminConfirmSignUp_Async* AdminConfirmSignUp_Async( FString Username, FString UserPoolId, TMap<FString, FString> ClientMetadata);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	TMap<FString, FString> Var_ClientMetadata;
	FString Var_Username;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FAdminConfirmSignUpResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminConfirmSignUpResponse OnFailure;
};
