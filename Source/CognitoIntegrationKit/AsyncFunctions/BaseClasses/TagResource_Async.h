
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "TagResource_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnTagResourceResult, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UTagResource_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UTagResource_Async* TagResource_Async(FString Resource_ARN, TMap<FString, FString> Tags);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY()
	FString Var_Resource_ARN;
	UPROPERTY()
	TMap<FString, FString> Var_Tags;
	
	UPROPERTY(BlueprintAssignable)
	FOnTagResourceResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnTagResourceResult OnFailure;



};
