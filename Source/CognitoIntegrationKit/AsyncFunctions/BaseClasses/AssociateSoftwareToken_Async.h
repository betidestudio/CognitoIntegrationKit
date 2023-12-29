
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AssociateSoftwareToken_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAssociateSoftwareTokenAsync, FString, AccessToken, FString, Session, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAssociateSoftwareToken_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAssociateSoftwareToken_Async* AssociateSoftwareToken_Async();

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;
	FString Var_Session;

	UPROPERTY(BlueprintAssignable)
	FOnAssociateSoftwareTokenAsync OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAssociateSoftwareTokenAsync OnFailure;
};
