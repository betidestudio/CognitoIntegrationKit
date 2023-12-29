
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminAddUserToGroup_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdminAddUserToGroupResponse, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminAddUserToGroup_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit", DisplayName = "Admin Add User To Group")
	static UAdminAddUserToGroup_Async* AdminAddUserToGroup_Async(FString GroupName, FString Username, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FAdminAddUserToGroupResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminAddUserToGroupResponse OnFailure;

	FString Var_GroupName;
	FString Var_Username;
	FString Var_UserPoolId;

};
