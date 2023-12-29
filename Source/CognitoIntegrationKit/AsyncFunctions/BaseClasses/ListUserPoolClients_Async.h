
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ListUserPoolClients_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListUserPoolClientsDelegate, FString, NextToken, TArray<FUserPoolClientDescription>, UserPoolClients, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UListUserPoolClients_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UListUserPoolClients_Async* ListUserPoolClients_Async(int32 MaxResults, FString NextToken, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	int32 Var_MaxResults;
	FString Var_NextToken;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FListUserPoolClientsDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListUserPoolClientsDelegate OnFailure;

};
