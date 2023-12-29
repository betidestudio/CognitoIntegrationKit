
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "GetIdentityProviderByIdentifier_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetIdentityProviderByIdentifierAsyncOutputPin, FIdentityProviderType, IdentityProvider, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UGetIdentityProviderByIdentifier_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UGetIdentityProviderByIdentifier_Async* GetIdentityProviderByIdentifier_Async(FString IdpIdentifier, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_IdpIdentifier;
	FString Var_UserPoolId;
	
	UPROPERTY(BlueprintAssignable)
	FGetIdentityProviderByIdentifierAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetIdentityProviderByIdentifierAsyncOutputPin OnFailure;

};
