
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminListUserAuthEvents_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FAdminListUserAuthEventsDelegate, TArray<FAuthEventType>, AuthEvents, FString, NextToken, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminListUserAuthEvents_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit", DisplayName = "Admin List User Auth Events")
	static UAdminListUserAuthEvents_Async* AdminListUserAuthEvents_Async(int32 MaxResults, FString NextToken, FString Username, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_NextToken;
	FString Var_Username;
	FString Var_UserPoolId;
	int32 Var_MaxResults;

	UPROPERTY(BlueprintAssignable)
		FAdminListUserAuthEventsDelegate OnSuccess;
	UPROPERTY(BlueprintAssignable)
		FAdminListUserAuthEventsDelegate OnFailure;
};
