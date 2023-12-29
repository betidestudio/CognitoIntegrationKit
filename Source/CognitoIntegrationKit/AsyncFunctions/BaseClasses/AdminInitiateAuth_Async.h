
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminInitiateAuth_Async.generated.h"

UENUM(BlueprintType)
enum AuthFlowType
{
	NOT_SET25 UMETA(DisplayName = "NOT_SET"),
	USER_SRP_AUTH,
	REFRESH_TOKEN_AUTH,
	REFRESH_TOKEN,
	CUSTOM_AUTH,
	ADMIN_NO_SRP_AUTH,
	USER_PASSWORD_AUTH,
	ADMIN_USER_PASSWORD_AUTH
  };


USTRUCT(BlueprintType)
struct FAdminInitiateAuthReq
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	FAnalyticsMetadataType AnalyticsMetadata;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	TEnumAsByte<AuthFlowType> AuthFlow;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	TMap<FString, FString> AuthParameters;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString ClientId;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	TMap<FString, FString> ClientMetadata;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	FContextDataType ContextData;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString UserPoolId;
};

USTRUCT(BlueprintType)
struct FAdminInitiateAuthResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	FAuthenticationResultType AuthenticationResult;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	TMap<FString, FString> ChallengeParameters;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString Session;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	TEnumAsByte<EChallengeName1> ChallengeName;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAdminInitiateAuthResponseMulti, FAdminInitiateAuthResponse, AdminInitiateAuthResponse, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminInitiateAuth_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminInitiateAuth_Async* AdminInitiateAuth_Async();

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FAdminInitiateAuthReq Var_Request;

	UPROPERTY(BlueprintAssignable)
	FAdminInitiateAuthResponseMulti OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminInitiateAuthResponseMulti OnFailure;
};
