
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "RespondToAuthChallenge_Async.generated.h"

USTRUCT(BlueprintType)
struct FRespondToAuthChallengeReq
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAnalyticsMetadataType AnalyticsMetadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EChallengeNameType> ChallengeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString,FString> ChallengeResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString ClientId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString, FString> ClientMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FUserContextDataType ContextData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Session;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FRespondToAuthChallengeResp
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<EChallengeName1> ChallengeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FString,FString> ChallengeParameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Session;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FAuthenticationResultType AuthenticationResult;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FRespondToAuthChallengeAsyncOutputPin, FCognitoError, Error, FRespondToAuthChallengeResp, Data);


UCLASS()
class COGNITOINTEGRATIONKIT_API URespondToAuthChallenge_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static URespondToAuthChallenge_Async* RespondToAuthChallenge_Async(FRespondToAuthChallengeReq Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FRespondToAuthChallengeReq Val_RespondToAuthChallengeReq;

	UPROPERTY(BlueprintAssignable)
	FRespondToAuthChallengeAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FRespondToAuthChallengeAsyncOutputPin OnFailure;
};
