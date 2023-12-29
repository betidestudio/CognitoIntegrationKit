
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "UpdateIdentityProvider_Async.generated.h"

USTRUCT(BlueprintType)
struct FUpdateIdentityProviderReq
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString UserPoolId;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString ProviderName;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Provider")
	TMap<FString,FString> ProviderDetails;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Provider")
	TMap<FString,FString> AttributeMapping;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Provider")
	TArray<FString> IdpIdentifiers;
	
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateIdentityProviderAsyncOutputPin, FIdentityProviderType,IdentityProvider,FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UUpdateIdentityProvider_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UUpdateIdentityProvider_Async* UpdateIdentityProvider_Async(FUpdateIdentityProviderReq Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FUpdateIdentityProviderAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FUpdateIdentityProviderAsyncOutputPin OnFailure;

	FUpdateIdentityProviderReq Var_UpdateIdentityProviderReq;
	

};
