
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ListTagsForResource_Async.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FListTagsForResourceResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> Tags;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FListTagsForResourceDelegate, FListTagsForResourceResponse, Response, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UListTagsForResource_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UListTagsForResource_Async* ListTagsForResource_Async(FString ResourceArn);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_ResourceArn;

	UPROPERTY(BlueprintAssignable)
	FListTagsForResourceDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListTagsForResourceDelegate OnFailure;

};
