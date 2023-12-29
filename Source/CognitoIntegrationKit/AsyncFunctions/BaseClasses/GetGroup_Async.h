
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "GetGroup_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetGroupResult, FGroupType, Group, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UGetGroup_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UGetGroup_Async* GetGroup_Async(FString GroupName, FString UserPoolID);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_GroupName;
	FString Var_UserPoolID;

	UPROPERTY(BlueprintAssignable)
	FGetGroupResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetGroupResult OnFailure;

};
