
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DeleteUser_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleteUserDelegate, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDeleteUser_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDeleteUser_Async* DeleteUser_Async(FString AccessToken);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;

	UPROPERTY(BlueprintAssignable)
	FDeleteUserDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDeleteUserDelegate OnFailure;

};
