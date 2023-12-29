
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "UntagResource_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUntagResourceResult, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UUntagResource_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UUntagResource_Async* UntagResource_Async(FString Resource_ARN,TArray<FString> TagKeys);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FOnUntagResourceResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnUntagResourceResult OnFailure;

	FString Var_Resource_ARN;
	TArray<FString> Var_TagKeys;

	

};
