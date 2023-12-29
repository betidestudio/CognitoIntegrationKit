
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "CreateIdentityProvider_Async.generated.h"


USTRUCT(BlueprintType)
struct FCreateIdentityProviderRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TMap<FString,FString> AttributeMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FString> IdpIdentifiers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TMap<FString, FString> ProviderDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ProviderName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EIdentityProviderType> ProviderType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString UserPoolId;

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FCreateIdentityProviderAsyncResponse, FIdentityProviderType, Result, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UCreateIdentityProvider_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UCreateIdentityProvider_Async* CreateIdentityProvider_Async(FCreateIdentityProviderRequest Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FCreateIdentityProviderAsyncResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FCreateIdentityProviderAsyncResponse OnFailure;

	FCreateIdentityProviderRequest Var_Request;

};
