
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "DescribeUserPoolDomain_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDescribeUserPoolDomain, FDomainDescriptionType, Domain, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UDescribeUserPoolDomain_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UDescribeUserPoolDomain_Async* DescribeUserPoolDomain_Async(FString Domain);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_Domain;

	UPROPERTY(BlueprintAssignable)
	FDescribeUserPoolDomain OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FDescribeUserPoolDomain OnFailure;

};
