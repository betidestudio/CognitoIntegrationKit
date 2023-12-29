
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "RevokeToken_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FRevokeTokenDelegate, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API URevokeToken_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static URevokeToken_Async* RevokeToken_Async(FString ClientId, FString ClientSecret, FString Token);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_ClientId;
	FString Var_ClientSecret;
	FString Var_Token;

	UPROPERTY(BlueprintAssignable)
	FRevokeTokenDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRevokeTokenDelegate OnFailure;
};
