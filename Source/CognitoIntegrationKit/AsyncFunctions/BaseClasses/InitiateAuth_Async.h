
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "InitiateAuth_Async.generated.h"

USTRUCT(BlueprintType)
struct FInitiateAuthRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	FAnalyticsMetadataType Metadata;
	
	UPROPERTY(BlueprintReadWrite)
	FString AuthFlow;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> AuthParameters;

	UPROPERTY(BlueprintReadWrite)
	FString ClientId;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> ClientMetadata;

	UPROPERTY(BlueprintReadWrite)
	FUserContextDataType UserContextData;
	
};
USTRUCT(BlueprintType)
struct FInitiateAuthResponse
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	FAuthenticationResultType AuthenticationResult;

	UPROPERTY(BlueprintReadWrite)
	TEnumAsByte<EChallengeNameType> ChallengeName;

	UPROPERTY(BlueprintReadWrite)
	TMap<FString, FString> ChallengeParameters;

	UPROPERTY(BlueprintReadWrite)
	FString Session;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInitiateAuthResult, FInitiateAuthResponse, InitiateAuthResponse, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UInitiateAuth_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UInitiateAuth_Async* InitiateAuth_Async(FInitiateAuthRequest Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FInitiateAuthRequest Var_InitiateAuthRequest;

	UPROPERTY(BlueprintAssignable)
	FInitiateAuthResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FInitiateAuthResult OnFailure;

};
