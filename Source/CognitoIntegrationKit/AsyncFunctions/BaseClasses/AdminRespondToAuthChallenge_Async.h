
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FAnalyticsMetadataType AnalyticsMetadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TEnumAsByte<EChallengeNameType> ChallengeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TMap<FString,FString> ChallengeResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString ClientId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TMap<FString, FString> ClientMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FContextDataType ContextData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString Session;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FAdminRespondToAuthChallengeResp
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TEnumAsByte<EChallengeName1> ChallengeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TMap<FString,FString> ChallengeParameters;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString Session;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
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
