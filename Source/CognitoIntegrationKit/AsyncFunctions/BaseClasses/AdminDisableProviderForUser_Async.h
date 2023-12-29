
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminDisableProviderForUser_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdminDisableProviderForUserAsync, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminDisableProviderForUser_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminDisableProviderForUser_Async* AdminDisableProviderForUser_Async(FProviderUserIdentifierType ProviderUserIdentifier, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FProviderUserIdentifierType Var_ProviderUserIdentifier;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FOnAdminDisableProviderForUserAsync OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAdminDisableProviderForUserAsync OnFailure;

};
