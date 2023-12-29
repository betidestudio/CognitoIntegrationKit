
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminRemoveUserFromGroup_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdminRemoveUserFromGroupDelegate, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminRemoveUserFromGroup_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminRemoveUserFromGroup_Async* AdminRemoveUserFromGroup_Async(FString GroupName, FString Username, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_GroupName;
	FString Var_Username;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FAdminRemoveUserFromGroupDelegate OnSuccess;
	
	UPROPERTY(BlueprintAssignable)
	FAdminRemoveUserFromGroupDelegate OnFailure;
};
