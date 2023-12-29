
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "UpdateUserPoolClient_Async.generated.h"

USTRUCT(BlueprintType)
struct FAnalyticsConfiguration
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString ApplicationArn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString ApplicationId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString ExternalId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString RoleArn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    bool UserDataShared = false;
};

USTRUCT(BlueprintType)
struct FTokenValidityUnits
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString AccessToken;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString IdToken;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString RefreshToken;
};

USTRUCT(BlueprintType)
struct FUpdateUserPoolRequest
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString ClientId = "";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    int32 AccessTokenValidity = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    TArray<FString> AllowedOAuthFlows = {};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    bool AllowedOAuthFlowsUserPoolClient = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    TArray<FString> AllowedOAuthScopes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FAnalyticsConfiguration AnalyticsConfiguration = {};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    int32 AuthSessionValidity = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    TArray<FString> CallbackURLs = {};

    // Note: ClientId is already declared above
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString ClientName = "";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString DefaultRedirectURI = "";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    bool EnablePropagateAdditionalUserContextData = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    bool EnableTokenRevocation = false;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    TArray<FString> ExplicitAuthFlows = {};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    int32 IdTokenValidity = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    TArray<FString> LogoutURLs = {};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString PreventUserExistenceErrors = "";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    TArray<FString> ReadAttributes = {};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    int32 RefreshTokenValidity = 0;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    TArray<FString> SupportedIdentityProviders = {};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FTokenValidityUnits TokenValidityUnits = {};

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    FString UserPoolId = "";

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
    TArray<FString> WriteAttributes = {};
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateUserPoolClientDelegate, FString, ClientSecret, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UUpdateUserPoolClient_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Cogntio Identity Kit")
	static UUpdateUserPoolClient_Async* UpdateUserPoolClient_Async(UObject* WorldContextObject, FUpdateUserPoolRequest UpdateUserPoolRequest);

	virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FUpdateUserPoolClientDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FUpdateUserPoolClientDelegate OnFailure;


	FUpdateUserPoolRequest Var_UpdateUserPoolRequest;
};
