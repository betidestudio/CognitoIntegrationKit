
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "CreateResourceServer_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateResourceServerDelegate, FResourceServerType, ResourceServer,FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UCreateResourceServer_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UCreateResourceServer_Async* CreateResourceServer_Async(FString UserPoolId, FString Identifier, FString Name, TArray<FResourceServerScopeType> ScopeType);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_UserPoolId;
	FString Var_Identifier;
	FString Var_Name;
	TArray<FResourceServerScopeType> Var_ScopeType;

	UPROPERTY(BlueprintAssignable)
	FCreateResourceServerDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateResourceServerDelegate OnFailure;

};
