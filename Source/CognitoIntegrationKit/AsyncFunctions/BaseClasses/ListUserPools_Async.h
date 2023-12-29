
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ListUserPools_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListUserPoolsDelegate, FString, NextToken, TArray<FUserPoolDescriptionType>, UserPools, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UListUserPools_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UListUserPools_Async* ListUserPools_Async(int32 MaxResults, FString NextToken);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	int32 Var_MaxResults;
	FString Var_NextToken;

	UPROPERTY(BlueprintAssignable)
	FListUserPoolsDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListUserPoolsDelegate OnFailure;

};
