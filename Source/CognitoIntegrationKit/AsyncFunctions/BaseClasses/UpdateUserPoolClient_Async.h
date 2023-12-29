
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

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ApplicationArn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ApplicationId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ExternalId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString RoleArn;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool UserDataShared = false;
};

USTRUCT(BlueprintType)
struct FTokenValidityUnits
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString AccessToken;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString IdToken;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString RefreshToken;
};

USTRUCT(BlueprintType)
struct FUpdateUserPoolRequest
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ClientId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AccessTokenValidity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> AllowedOAuthFlows;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool AllowedOAuthFlowsUserPoolClient;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> AllowedOAuthScopes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FAnalyticsConfiguration AnalyticsConfiguration;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 AuthSessionValidity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> CallbackURLs;

    // Note: ClientId is already declared above
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString ClientName;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString DefaultRedirectURI;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool EnablePropagateAdditionalUserContextData;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    bool EnableTokenRevocation;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ExplicitAuthFlows;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 IdTokenValidity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> LogoutURLs;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString PreventUserExistenceErrors;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> ReadAttributes;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    int32 RefreshTokenValidity;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> SupportedIdentityProviders;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FTokenValidityUnits TokenValidityUnits;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FString UserPoolId;

    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    TArray<FString> WriteAttributes;
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
