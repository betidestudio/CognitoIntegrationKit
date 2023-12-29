
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "GetSigningCertificate_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetSigningCertificateDelegate, FString, SigningCertificate, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UGetSigningCertificate_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UGetSigningCertificate_Async* GetSigningCertificate_Async(FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FGetSigningCertificateDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetSigningCertificateDelegate OnFailure;
	
};
