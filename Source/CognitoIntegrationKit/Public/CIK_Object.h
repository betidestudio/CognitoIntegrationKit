//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "aws/cognito-idp/CognitoIdentityProviderClient.h"
#include "UObject/NoExportTypes.h"
#include "CIK_Object.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FOnCognitoIdentityKitSetupComplete, bool, bWasSuccessful, UCIK_Object*, CognitoObject);

UENUM(BlueprintType)
enum ECognitoErrors
{
	  //From Core//
  //////////////////////////////////////////////////////////////////////////////////////////
  INCOMPLETE_SIGNATURE = 0,
  INTERNAL_FAILURE = 1,
  INVALID_ACTION = 2,
  INVALID_CLIENT_TOKEN_ID = 3,
  INVALID_PARAMETER_COMBINATION = 4,
  INVALID_QUERY_PARAMETER = 5,
  INVALID_PARAMETER_VALUE = 6,
  MISSING_ACTION = 7, // SDK should never allow
  MISSING_AUTHENTICATION_TOKEN = 8, // SDK should never allow
  MISSING_PARAMETER = 9, // SDK should never allow
  OPT_IN_REQUIRED = 10,
  REQUEST_EXPIRED = 11,
  SERVICE_UNAVAILABLE = 12,
  THROTTLING = 13,
  VALIDATION = 14,
  ACCESS_DENIED = 15,
  RESOURCE_NOT_FOUND = 16,
  UNRECOGNIZED_CLIENT = 17,
  MALFORMED_QUERY_STRING = 18,
  SLOW_DOWN = 19,
  REQUEST_TIME_TOO_SKEWED = 20,
  INVALID_SIGNATURE = 21,
  SIGNATURE_DOES_NOT_MATCH = 22,
  INVALID_ACCESS_KEY_ID = 23,
  REQUEST_TIMEOUT = 24,
  NETWORK_CONNECTION = 99,

  UNKNOWN = 100,
  ///////////////////////////////////////////////////////////////////////////////////////////

  ALIAS_EXISTS= static_cast<int>(Aws::Client::CoreErrors::SERVICE_EXTENSION_START_RANGE) + 1,
  CODE_DELIVERY_FAILURE,
  CODE_MISMATCH,
  CONCURRENT_MODIFICATION,
  DUPLICATE_PROVIDER,
  ENABLE_SOFTWARE_TOKEN_M_F_A,
  EXPIRED_CODE,
  FORBIDDEN,
  GROUP_EXISTS,
  INTERNAL_ERROR,
  INVALID_EMAIL_ROLE_ACCESS_POLICY,
  INVALID_LAMBDA_RESPONSE,
  INVALID_O_AUTH_FLOW,
  INVALID_PARAMETER,
  INVALID_PASSWORD,
  INVALID_SMS_ROLE_ACCESS_POLICY,
  INVALID_SMS_ROLE_TRUST_RELATIONSHIP,
  INVALID_USER_POOL_CONFIGURATION,
  LIMIT_EXCEEDED,
  M_F_A_METHOD_NOT_FOUND,
  NOT_AUTHORIZED,
  PASSWORD_RESET_REQUIRED,
  PRECONDITION_NOT_MET,
  SCOPE_DOES_NOT_EXIST,
  SOFTWARE_TOKEN_M_F_A_NOT_FOUND,
  TOO_MANY_FAILED_ATTEMPTS,
  TOO_MANY_REQUESTS,
  UNAUTHORIZED,
  UNEXPECTED_LAMBDA,
  UNSUPPORTED_IDENTITY_PROVIDER,
  UNSUPPORTED_OPERATION,
  UNSUPPORTED_TOKEN_TYPE,
  UNSUPPORTED_USER_STATE,
  USERNAME_EXISTS,
  USER_IMPORT_IN_PROGRESS,
  USER_LAMBDA_VALIDATION,
  USER_NOT_CONFIRMED,
  USER_NOT_FOUND,
  USER_POOL_ADD_ON_NOT_ENABLED,
  USER_POOL_TAGGING
};

USTRUCT(BlueprintType)
struct FCognitoError
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ErrorMessage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GetMessageA;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GetMessageW;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ExceptionName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TEnumAsByte<ECognitoErrors> ErrorType = ECognitoErrors::UNKNOWN;
};

USTRUCT(BlueprintType)
struct FSetupCognito
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cognito Integration Kit")
	FString AccessKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cognito Integration Kit")
	FString SecretKey;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cognito Integration Kit")
	FString SessionToken;	
};

UENUM(BlueprintType)
enum EAWSServiceRegion
{
    aws_global        UMETA(DisplayName = "AWS Global"),
    us_east_1         UMETA(DisplayName = "US East 1 (N. Virginia)"),
    us_east_2         UMETA(DisplayName = "US East 2 (Ohio)"),
    us_west_1         UMETA(DisplayName = "US West 1 (N. California)"),
    us_west_2         UMETA(DisplayName = "US West 2 (Oregon)"),
    eu_west_1         UMETA(DisplayName = "EU West 1 (Ireland)"),
    eu_west_2         UMETA(DisplayName = "EU West 2 (London)"),
    eu_west_3         UMETA(DisplayName = "EU West 3 (Paris)"),
    eu_central_1      UMETA(DisplayName = "EU Central 1 (Frankfurt)"),
    eu_central_2      UMETA(DisplayName = "EU Central 2 (Zurich)"),
    eu_north_1        UMETA(DisplayName = "EU North 1 (Stockholm)"),
    eu_south_1        UMETA(DisplayName = "EU South 1 (Milan)"),
    eu_south_2        UMETA(DisplayName = "EU South 2 (Spain)"),
    ap_east_1         UMETA(DisplayName = "Asia Pacific East 1 (Hong Kong)"),
    ap_south_1        UMETA(DisplayName = "Asia Pacific South 1 (Mumbai)"),
    ap_south_2        UMETA(DisplayName = "Asia Pacific South 2 (Hyderabad)"),
    ap_southeast_1    UMETA(DisplayName = "Asia Pacific Southeast 1 (Singapore)"),
    ap_southeast_2    UMETA(DisplayName = "Asia Pacific Southeast 2 (Sydney)"),
    ap_southeast_3    UMETA(DisplayName = "Asia Pacific Southeast 3 (Jakarta)"),
    ap_northeast_1    UMETA(DisplayName = "Asia Pacific Northeast 1 (Tokyo)"),
    ap_northeast_2    UMETA(DisplayName = "Asia Pacific Northeast 2 (Seoul)"),
    ap_northeast_3    UMETA(DisplayName = "Asia Pacific Northeast 3 (Osaka)"),
    ap_northeast_4    UMETA(DisplayName = "Asia Pacific Northeast 4 (Melbourne)"),
    sa_east_1         UMETA(DisplayName = "South America East 1 (Sao Paulo)"),
    cn_north_1        UMETA(DisplayName = "China North 1 (Beijing)"),
    cn_northwest_1    UMETA(DisplayName = "China Northwest 1 (Ningxia)"),
    ca_central_1      UMETA(DisplayName = "Canada Central 1 (Central)"),
    me_south_1        UMETA(DisplayName = "Middle East South 1 (Bahrain)"),
    me_central_1      UMETA(DisplayName = "Middle East Central 1 (UAE)"),
    af_south_1        UMETA(DisplayName = "Africa South 1 (Cape Town)"),
    us_gov_west_1     UMETA(DisplayName = "AWS GovCloud West 1 (US-West)"),
    us_gov_east_1     UMETA(DisplayName = "AWS GovCloud East 1 (US-East)"),
    us_iso_east_1     UMETA(DisplayName = "US ISO East 1"),
    us_isob_east_1    UMETA(DisplayName = "US ISOB East 1 (Ohio)"),
    us_iso_west_1     UMETA(DisplayName = "US ISO West 1")
};


USTRUCT(BlueprintType)
struct FConfig
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Cognito Integration Kit")
	TEnumAsByte<EAWSServiceRegion> Region;
	
};

UCLASS(Blueprintable, BlueprintType)
class COGNITOINTEGRATIONKIT_API UCIK_Object : public UObject
{
	GENERATED_BODY()

public:

	FString CognitoClientID;
	Aws::CognitoIdentityProvider::CognitoIdentityProviderClient* Var_CognitoIPClient = nullptr;
	Aws::Client::ClientConfiguration* Var_ClientConfig = nullptr;

	
	UFUNCTION()
	void SetupObject(UObject* WorldContextObject, const FString& ClientID, FSetupCognito Credentials, FConfig Config, FOnCognitoIdentityKitSetupComplete OnSetupComplete);
	
	
};
