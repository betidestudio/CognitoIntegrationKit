
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DeleteUserPoolDomain_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeleteUserPoolDomainDelegate, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDeleteUserPoolDomain_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDeleteUserPoolDomain_Async* DeleteUserPoolDomain_Async(FString Domain, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_Domain;
	FString Var_UserPoolId;
	
	UPROPERTY(BlueprintAssignable)
	FDeleteUserPoolDomainDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDeleteUserPoolDomainDelegate OnFailure;

};
