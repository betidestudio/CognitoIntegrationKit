
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CIK_Object.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UpdateUserPoolDomain_Async.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateUserPoolDomain_Delegate, FString, CloudFrontDomain, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UUpdateUserPoolDomain_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Cogntio Identity Kit")
	static UUpdateUserPoolDomain_Async* UpdateUserPoolDomain_Async(UObject* WorldContextObject, FString Domain, FString UserPoolID, FString CertificateArn);


	virtual void ContinueProcess(UCIK_Object* CognitoObject) override;
	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_Domain;
	FString Var_UserPoolID;
	FString Var_CustomDomainConfig_CertificateArn;

	UPROPERTY(BlueprintAssignable)
	FUpdateUserPoolDomain_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FUpdateUserPoolDomain_Delegate OnFailure;
};
