
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminDeleteUserAttributes_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdminDeleteUserAttributesDelegate, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminDeleteUserAttributes_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminDeleteUserAttributes_Async* AdminDeleteUserAttributes_Async(TArray<FString> UserAttributeNames, FString Username, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	TArray<FString> Var_UserAttributeNames;
	FString Var_Username;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FAdminDeleteUserAttributesDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminDeleteUserAttributesDelegate OnFailure;
};
