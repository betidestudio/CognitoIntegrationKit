
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminRespondToAuthChallenge_Async.generated.h"

USTRUCT(BlueprintType)
struct FAdminRespondToAuthChallengeReq
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
	FContextDataType ContextData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Session;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FAdminRespondToAuthChallengeResp
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

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAdminRespondToAuthChallengeAsyncOutputPin, FCognitoError, Error, FAdminRespondToAuthChallengeResp, Data);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminRespondToAuthChallenge_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminRespondToAuthChallenge_Async* AdminRespondToAuthChallenge_Async(FAdminRespondToAuthChallengeReq Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FAdminRespondToAuthChallengeReq Val_AdminRespondToAuthChallengeReq;

	UPROPERTY(BlueprintAssignable)
	FAdminRespondToAuthChallengeAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminRespondToAuthChallengeAsyncOutputPin OnFailure;
};
