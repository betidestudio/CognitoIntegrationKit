//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include <aws/cognito-idp/CognitoIdentityProvider_EXPORTS.h>
#include <aws/core/auth/AWSCredentials.h>
#include <aws/cognito-idp/model/MFAOptionType.h>
#include <aws/cognito-identity/CognitoIdentityClient.h>
#include <aws/cognito-idp/CognitoIdentityProviderClient.h>
#include <aws/cognito-idp/model/AnalyticsMetadataType.h>
#include <aws/cognito-idp/model/UserContextDataType.h>
#include <aws/cognito-idp/model/AddCustomAttributesResult.h>
#include <aws/cognito-idp/model/AdminConfirmSignUpResult.h>
#include <aws/cognito-idp/model/AdminCreateUserResult.h>
#include <aws/cognito-idp/model/AdminDeleteUserAttributesResult.h>
#include <aws/cognito-idp/model/AdminDisableProviderForUserResult.h>
#include <aws/cognito-idp/model/AdminDisableUserResult.h>
#include <aws/cognito-idp/model/AdminEnableUserResult.h>
#include <aws/cognito-idp/model/AdminGetDeviceResult.h>
#include <aws/cognito-idp/model/AdminGetUserResult.h>
#include <aws/cognito-idp/model/AdminInitiateAuthResult.h>
#include <aws/cognito-idp/model/AdminLinkProviderForUserResult.h>
#include <aws/cognito-idp/model/AdminListDevicesResult.h>
#include <aws/cognito-idp/model/AdminListGroupsForUserResult.h>
#include <aws/cognito-idp/model/AdminListUserAuthEventsResult.h>
#include <aws/cognito-idp/model/AdminResetUserPasswordResult.h>
#include <aws/cognito-idp/model/AdminRespondToAuthChallengeResult.h>
#include <aws/cognito-idp/model/AdminSetUserMFAPreferenceResult.h>
#include <aws/cognito-idp/model/AdminSetUserPasswordResult.h>
#include <aws/cognito-idp/model/AdminSetUserSettingsResult.h>
#include <aws/cognito-idp/model/AdminUpdateAuthEventFeedbackResult.h>
#include <aws/cognito-idp/model/AdminUpdateDeviceStatusResult.h>
#include <aws/cognito-idp/model/AdminUpdateUserAttributesResult.h>
#include <aws/cognito-idp/model/AdminUserGlobalSignOutResult.h>
#include <aws/cognito-idp/model/AssociateSoftwareTokenResult.h>
#include <aws/cognito-idp/model/ChangePasswordResult.h>
#include <aws/cognito-idp/model/ConfirmDeviceResult.h>
#include <aws/cognito-idp/model/ConfirmForgotPasswordResult.h>
#include <aws/cognito-idp/model/ConfirmSignUpResult.h>
#include <aws/cognito-idp/model/CreateGroupResult.h>
#include <aws/cognito-idp/model/CreateIdentityProviderResult.h>
#include <aws/cognito-idp/model/CreateResourceServerResult.h>
#include <aws/cognito-idp/model/CreateUserImportJobResult.h>
#include <aws/cognito-idp/model/CreateUserPoolResult.h>
#include <aws/cognito-idp/model/CreateUserPoolClientResult.h>
#include <aws/cognito-idp/model/CreateUserPoolDomainResult.h>
#include <aws/cognito-idp/model/DeleteUserAttributesResult.h>
#include <aws/cognito-idp/model/DeleteUserPoolDomainResult.h>
#include <aws/cognito-idp/model/DescribeIdentityProviderResult.h>
#include <aws/cognito-idp/model/DescribeResourceServerResult.h>
#include <aws/cognito-idp/model/DescribeRiskConfigurationResult.h>
#include <aws/cognito-idp/model/DescribeUserImportJobResult.h>
#include <aws/cognito-idp/model/DescribeUserPoolResult.h>
#include <aws/cognito-idp/model/DescribeUserPoolClientResult.h>
#include <aws/cognito-idp/model/DescribeUserPoolDomainResult.h>
#include <aws/cognito-idp/model/ForgotPasswordResult.h>
#include <aws/cognito-idp/model/GetCSVHeaderResult.h>
#include <aws/cognito-idp/model/GetDeviceResult.h>
#include <aws/cognito-idp/model/GetGroupResult.h>
#include <aws/cognito-idp/model/GetIdentityProviderByIdentifierResult.h>
#include <aws/cognito-idp/model/GetSigningCertificateResult.h>
#include <aws/cognito-idp/model/GetUICustomizationResult.h>
#include <aws/cognito-idp/model/GetUserResult.h>
#include <aws/cognito-idp/model/GetUserAttributeVerificationCodeResult.h>
#include <aws/cognito-idp/model/GetUserPoolMfaConfigResult.h>
#include <aws/cognito-idp/model/GlobalSignOutResult.h>
#include <aws/cognito-idp/model/InitiateAuthResult.h>
#include <aws/cognito-idp/model/ListDevicesResult.h>
#include <aws/cognito-idp/model/ListGroupsResult.h>
#include <aws/cognito-idp/model/ListIdentityProvidersResult.h>
#include <aws/cognito-idp/model/ListResourceServersResult.h>
#include <aws/cognito-idp/model/ListTagsForResourceResult.h>
#include <aws/cognito-idp/model/ListUserImportJobsResult.h>
#include <aws/cognito-idp/model/ListUserPoolClientsResult.h>
#include <aws/cognito-idp/model/ListUserPoolsResult.h>
#include <aws/cognito-idp/model/ListUsersResult.h>
#include <aws/cognito-idp/model/ListUsersInGroupResult.h>
#include <aws/cognito-idp/model/ResendConfirmationCodeResult.h>
#include <aws/cognito-idp/model/RespondToAuthChallengeResult.h>
#include <aws/cognito-idp/model/SetRiskConfigurationResult.h>
#include <aws/cognito-idp/model/SetUICustomizationResult.h>
#include <aws/cognito-idp/model/SetUserMFAPreferenceResult.h>
#include <aws/cognito-idp/model/SetUserPoolMfaConfigResult.h>
#include <aws/cognito-idp/model/SetUserSettingsResult.h>
#include <aws/cognito-idp/model/SignUpResult.h>
#include <aws/cognito-idp/model/StartUserImportJobResult.h>
#include <aws/cognito-idp/model/StopUserImportJobResult.h>
#include <aws/cognito-idp/model/UpdateAuthEventFeedbackResult.h>
#include <aws/cognito-idp/model/UpdateDeviceStatusResult.h>
#include <aws/cognito-idp/model/UpdateGroupResult.h>
#include <aws/cognito-idp/model/UpdateIdentityProviderResult.h>
#include <aws/cognito-idp/model/UpdateResourceServerResult.h>
#include <aws/cognito-idp/model/UpdateUserAttributesResult.h>
#include <aws/cognito-idp/model/UpdateUserPoolResult.h>
#include <aws/cognito-idp/model/UpdateUserPoolClientResult.h>
#include <aws/cognito-idp/model/UpdateUserPoolDomainResult.h>
#include <aws/cognito-idp/model/VerifySoftwareTokenResult.h>
#include <aws/cognito-idp/model/VerifyUserAttributeResult.h>
#include <aws/cognito-idp/model/DeviceSecretVerifierConfigType.h>
#include "aws/cognito-idp/model/HttpHeader.h"
#include "aws/cognito-idp/model/SMSMfaSettingsType.h"
#include "aws/cognito-idp/model/SoftwareTokenMfaSettingsType.h"
#include "aws/cognito-idp/model/ContextDataType.h"
#include "aws/cognito-idp/model/ProviderUserIdentifierType.h"
#include "aws/cognito-idp/model/TokenValidityUnitsType.h"
#include "aws/cognito-idp/model/AccountRecoverySettingType.h"
#include "aws/cognito-idp/model/AnalyticsConfigurationType.h"
#include "aws/cognito-idp/model/AnalyticsMetadataType.h"
#include "aws/cognito-idp/model/AuthenticationResultType.h"
#include "aws/cognito-idp/model/AuthEventType.h"
#include "aws/cognito-idp/model/CloudWatchLogsConfigurationType.h"
#include "aws/cognito-idp/model/CodeDeliveryDetailsType.h"
#include "aws/cognito-idp/model/DeviceSecretVerifierConfigType.h"
#include "aws/cognito-idp/model/DeviceType.h"
#include "aws/cognito-idp/model/DomainDescriptionType.h"
#include "aws/cognito-idp/model/GroupType.h"
#include "aws/cognito-idp/model/HttpHeader.h"
#include "aws/cognito-idp/model/IdentityProviderType.h"
#include "aws/cognito-idp/model/LogConfigurationType.h"
#include "aws/cognito-idp/model/LogDeliveryConfigurationType.h"
#include "aws/cognito-idp/model/PasswordPolicyType.h"
#include "aws/cognito-idp/model/ProviderDescription.h"
#include "aws/cognito-idp/model/ProviderUserIdentifierType.h"
#include "aws/cognito-idp/model/RecoveryOptionType.h"
#include "aws/cognito-idp/model/ResourceServerScopeType.h"
#include "aws/cognito-idp/model/ResourceServerType.h"
#include "aws/cognito-idp/model/RiskConfigurationType.h"
#include "aws/cognito-idp/model/SmsConfigurationType.h"
#include "aws/cognito-idp/model/SmsMfaConfigType.h"
#include "aws/cognito-idp/model/SMSMfaSettingsType.h"
#include "aws/cognito-idp/model/SoftwareTokenMfaConfigType.h"
#include "aws/cognito-idp/model/SoftwareTokenMfaSettingsType.h"
#include "aws/cognito-idp/model/UserPoolType.h"
#include "aws/cognito-idp/model/UserType.h"
#include "aws/cognito-idp/model/VerificationMessageTemplateType.h"
#include "aws/core/utils/DateTime.h"
#include "aws/cognito-idp/model/AccountTakeoverActionType.h"
#include "aws/cognito-idp/model/AccountTakeoverActionsType.h"
#include "aws/cognito-idp/model/AttributeType.h"
#include "aws/cognito-idp/model/CompromisedCredentialsActionsType.h"
#include "aws/cognito-idp/model/CompromisedCredentialsRiskConfigurationType.h"
#include "aws/cognito-idp/model/ContextDataType.h"
#include "aws/cognito-idp/model/CustomDomainConfigType.h"
#include "aws/cognito-idp/model/CustomEmailLambdaVersionConfigType.h"
#include "aws/cognito-idp/model/CustomSMSLambdaVersionConfigType.h"
#include "aws/cognito-idp/model/DeviceConfigurationType.h"
#include "aws/cognito-idp/model/EventContextDataType.h"

#include "aws/cognito-idp/model/EventFeedbackType.h"
#include "aws/cognito-idp/model/EventRiskType.h"
#include "aws/cognito-idp/model/EventType.h"
#include "aws/cognito-idp/model/HttpHeader.h"
#include "aws/cognito-idp/model/NotifyConfigurationType.h"
#include "aws/cognito-idp/model/NotifyEmailType.h"
#include "aws/cognito-idp/model/PasswordPolicyType.h"
#include "aws/cognito-idp/model/ResourceServerScopeType.h"
#include "aws/cognito-idp/model/EmailConfigurationType.h"
#include "aws/cognito-idp/model/DeviceSecretVerifierConfigType.h"
#include "aws/cognito-idp/model/DeviceType.h"
#include "aws/cognito-idp/model/NotifyEmailType.h"
#include "aws/cognito-idp/model/NumberAttributeConstraintsType.h"
#include "aws/cognito-idp/model/PasswordPolicyType.h"
#include "aws/cognito-idp/model/AuthEventType.h"
#include "aws/cognito-idp/model/AttributeType.h"
#include "aws/cognito-idp/model/ChallengeResponseType.h"
#include "UObject/Object.h"

#include "CognitoDataTypes.generated.h"

UENUM(BlueprintType)
enum EAccountTakeoverEventActionType
{
	NOT_SET,
	BLOCK,
	MFA_IF_CONFIGURED,
	MFA_REQUIRED,
	NO_ACTION
};


USTRUCT(BlueprintType)
struct FAccountTakeoverActionType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool Notify;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EAccountTakeoverEventActionType> EventAction;

	FAccountTakeoverActionType()
	: Notify(false), EventAction(EAccountTakeoverEventActionType::NOT_SET) // Initialize with default values
{
}
	
	FAccountTakeoverActionType(const Aws::CognitoIdentityProvider::Model::AccountTakeoverActionType& AccountTakeoverActionType)
	{
		Notify = AccountTakeoverActionType.GetNotify();
		EventAction = static_cast<EAccountTakeoverEventActionType>(AccountTakeoverActionType.GetEventAction());
	}
	Aws::CognitoIdentityProvider::Model::AccountTakeoverActionType GetAccountTakeoverActionType()
	{
		Aws::CognitoIdentityProvider::Model::AccountTakeoverActionType AccountTakeoverActionType;
		AccountTakeoverActionType.SetNotify(Notify);
		AccountTakeoverActionType.SetEventAction(static_cast<Aws::CognitoIdentityProvider::Model::AccountTakeoverEventActionType>(EventAction.GetValue()));
		return AccountTakeoverActionType;
	}
	
};

USTRUCT(BlueprintType)
struct FAccountTakeoverActionsType
{
	GENERATED_BODY()

	// Assuming AccountTakeoverActionType is another custom struct you have defined.
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FAccountTakeoverActionType LowAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FAccountTakeoverActionType MediumAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FAccountTakeoverActionType HighAction;

	FAccountTakeoverActionsType()
	{
	}
	FAccountTakeoverActionsType(const Aws::CognitoIdentityProvider::Model::AccountTakeoverActionsType& AccountTakeoverActionsType)
	{
		LowAction = FAccountTakeoverActionType(AccountTakeoverActionsType.GetLowAction());
		MediumAction = FAccountTakeoverActionType(AccountTakeoverActionsType.GetMediumAction());
		HighAction = FAccountTakeoverActionType(AccountTakeoverActionsType.GetHighAction());
	}
	Aws::CognitoIdentityProvider::Model::AccountTakeoverActionsType ToAccountTakeoverActionsType()
	{
		Aws::CognitoIdentityProvider::Model::AccountTakeoverActionsType AccountTakeoverActionsType;
		AccountTakeoverActionsType.SetLowAction(LowAction.GetAccountTakeoverActionType());
		AccountTakeoverActionsType.SetMediumAction(MediumAction.GetAccountTakeoverActionType());
		AccountTakeoverActionsType.SetHighAction(HighAction.GetAccountTakeoverActionType());
		return AccountTakeoverActionsType;
	}
};


USTRUCT(BlueprintType)
struct FAnalyticsConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ApplicationId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString RoleArn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ExternalId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ApplicationArn;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool UserDataShared;

	FAnalyticsConfigurationType(){}
	FAnalyticsConfigurationType(const Aws::CognitoIdentityProvider::Model::AnalyticsConfigurationType& Configuration)
	{
		ApplicationId = Configuration.GetApplicationId().c_str();
		ExternalId = Configuration.GetExternalId().c_str();
		RoleArn = Configuration.GetRoleArn().c_str();
		UserDataShared = Configuration.GetUserDataShared();
		ApplicationArn = Configuration.GetApplicationArn().c_str();
	}
};

USTRUCT(BlueprintType)
struct FAnalyticsMetadataType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString AnalyticsEndpointId;

	FAnalyticsMetadataType(){}
	
	FAnalyticsMetadataType(const Aws::CognitoIdentityProvider::Model::AnalyticsMetadataType& AnalyticsMetadataType)
	{
		AnalyticsEndpointId = AnalyticsMetadataType.GetAnalyticsEndpointId().c_str();
	}
	Aws::CognitoIdentityProvider::Model::AnalyticsMetadataType ToAnalyticsMetadataType()
	{
		Aws::CognitoIdentityProvider::Model::AnalyticsMetadataType AnalyticsMetadataType;
		AnalyticsMetadataType.SetAnalyticsEndpointId(TCHAR_TO_UTF8(*AnalyticsEndpointId));
		return AnalyticsMetadataType;
	}
};

UENUM(BlueprintType)
enum EChallengeNameType
{
	NOT_SET26 UMETA(DisplayName = "NOT_SET"),
	SMS_MFA,
	SOFTWARE_TOKEN_MFA,
	SELECT_MFA_TYPE,
	MFA_SETUP,
	PASSWORD_VERIFIER,
	CUSTOM_CHALLENGE,
	DEVICE_SRP_AUTH,
	DEVICE_PASSWORD_VERIFIER,
	ADMIN_NO_SRP_AUTH1 UMETA(DisplayName = "ADMIN_NO_SRP_AUTH"),
	NEW_PASSWORD_REQUIRED
  };
USTRUCT(BlueprintType)
struct FAttributeType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Name;  // The name of the attribute.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Value;  // The value of the attribute.

	FAttributeType(){}
	FAttributeType(const Aws::CognitoIdentityProvider::Model::AttributeType& AttributeType)
	{
		Name = AttributeType.GetName().c_str();
		Value = AttributeType.GetValue().c_str();
	}
	Aws::CognitoIdentityProvider::Model::AttributeType ToAttributeType()
	{
		Aws::CognitoIdentityProvider::Model::AttributeType AttributeType;
		AttributeType.SetName(TCHAR_TO_UTF8(*Name));
		AttributeType.SetValue(TCHAR_TO_UTF8(*Value));
		return AttributeType;
	}
};


USTRUCT(BlueprintType)
struct FNewDeviceMetadataType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString DeviceKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString DeviceGroupKey;

	FNewDeviceMetadataType(){}
	FNewDeviceMetadataType(const Aws::CognitoIdentityProvider::Model::NewDeviceMetadataType& NewDeviceMetadataType)
	{
		DeviceKey = NewDeviceMetadataType.GetDeviceKey().c_str();
		DeviceGroupKey = NewDeviceMetadataType.GetDeviceGroupKey().c_str();
	}
};


USTRUCT(BlueprintType)
struct FAuthenticationResultType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString AccessToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	int32 ExpiresIn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString TokenType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString RefreshToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString IdToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FNewDeviceMetadataType NewDeviceMetadata;

	FAuthenticationResultType(){}
	FAuthenticationResultType(const Aws::CognitoIdentityProvider::Model::AuthenticationResultType& AuthenticationResultType)
	{
		AccessToken = AuthenticationResultType.GetAccessToken().c_str();
		ExpiresIn = AuthenticationResultType.GetExpiresIn();
		TokenType = AuthenticationResultType.GetTokenType().c_str();
		RefreshToken = AuthenticationResultType.GetRefreshToken().c_str();
		IdToken = AuthenticationResultType.GetIdToken().c_str();
		NewDeviceMetadata = FNewDeviceMetadataType(AuthenticationResultType.GetNewDeviceMetadata());
	}
};

UENUM(BlueprintType)
enum EEventType
{
	NOT_SET13 UMETA(DisplayName = "NOT_SET"),
	SignIn,
	SignUp,
	ForgotPassword,
	PasswordChange,
	ResendCode
  };

UENUM(BlueprintType)
enum EEventResponseType
{
	NOT_SET14 UMETA(DisplayName = "NOT_SET"),
	Pass,
	Fail,
	InProgress
  };

UENUM(BlueprintType)
enum ERiskDecisionType
{
	NOT_SET15 UMETA(DisplayName = "NOT_SET"),
	NoRisk,
	AccountTakeover,
	Block
  };

UENUM(BlueprintType)
enum ERiskLevelType
{
	NOT_SET16 UMETA(DisplayName = "NOT_SET"),
	Low,
	Medium,
	High
  };

USTRUCT(BlueprintType)
struct FEventRiskType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool CompromisedCredentialsDetected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<ERiskDecisionType> RiskDecision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<ERiskLevelType> RiskLevel;
		
	
	FEventRiskType(){}
	FEventRiskType(const Aws::CognitoIdentityProvider::Model::EventRiskType& EventRiskType)
	{
		CompromisedCredentialsDetected = EventRiskType.GetCompromisedCredentialsDetected();
		RiskDecision = static_cast<ERiskDecisionType>(EventRiskType.GetRiskDecision());
		RiskLevel = static_cast<ERiskLevelType>(EventRiskType.GetRiskLevel());
	}
};
UENUM(BlueprintType)
enum EChallengeName1
{
	NOT_SET17 UMETA(DisplayName = "NOT_SET"),
	Password,
	Mfa
  };

UENUM(BlueprintType)
enum EChallengeResponse
{
	NOT_SET18 UMETA(DisplayName = "NOT_SET"),
	Success,
	Failure
  };

USTRUCT(BlueprintType)
struct FChallengeResponseType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EChallengeName1> ChallengeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EChallengeResponse> ChallengeResponse;

	FChallengeResponseType(){}
	FChallengeResponseType(const Aws::CognitoIdentityProvider::Model::ChallengeResponseType& ChallengeResponseType)
	{
		ChallengeName = static_cast<EChallengeName1>(ChallengeResponseType.GetChallengeName());
		ChallengeResponse = static_cast<EChallengeResponse>(ChallengeResponseType.GetChallengeResponse());
	}
};

USTRUCT(BlueprintType)
struct FAuthEventType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString EventId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EEventType> EventType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime CreationDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EEventResponseType> EventResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FEventRiskType EventRisk;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FChallengeResponseType> ChallengeResponses;  // Assuming this is a string, adjust as necessary.

	FAuthEventType(){}
	FAuthEventType(const Aws::CognitoIdentityProvider::Model::AuthEventType& AuthEventType)
	{
		EventId = AuthEventType.GetEventId().c_str();
		EventType = static_cast<EEventType>(AuthEventType.GetEventType());
		EventResponse = static_cast<EEventResponseType>(AuthEventType.GetEventResponse());
		EventRisk = AuthEventType.GetEventRisk();
		const Aws::Vector<Aws::CognitoIdentityProvider::Model::ChallengeResponseType>& ChallengeResponsesVector = AuthEventType.GetChallengeResponses();
		for (int i = 0; i < ChallengeResponsesVector.size(); i++)
		{
			ChallengeResponses.Add(FChallengeResponseType(ChallengeResponsesVector[i]));
		}
	}
};




USTRUCT(BlueprintType)
struct FCloudWatchLogsConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString LogGroupArn;
	FCloudWatchLogsConfigurationType(){}
	FCloudWatchLogsConfigurationType(const Aws::CognitoIdentityProvider::Model::CloudWatchLogsConfigurationType& CloudWatchLogsConfigurationType)
	{
		LogGroupArn = CloudWatchLogsConfigurationType.GetLogGroupArn().c_str();
	}
	Aws::CognitoIdentityProvider::Model::CloudWatchLogsConfigurationType ToCloudWatchLogsConfigurationType()
	{
		Aws::CognitoIdentityProvider::Model::CloudWatchLogsConfigurationType CloudWatchLogsConfigurationType;
		CloudWatchLogsConfigurationType.SetLogGroupArn(TCHAR_TO_UTF8(*LogGroupArn));
		return CloudWatchLogsConfigurationType;
	}
};

UENUM(BlueprintType)
enum EDeliveryMediumType
{
	NOT_SET5 UMETA(DisplayName = "NOT_SET"),
	SMS,
	EMAIL
  };


USTRUCT(BlueprintType)
struct FCodeDeliveryDetailsType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Destination;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EDeliveryMediumType> DeliveryMedium;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString AttributeName;

	FCodeDeliveryDetailsType(){}
	
	FCodeDeliveryDetailsType(const Aws::CognitoIdentityProvider::Model::CodeDeliveryDetailsType& CodeDeliveryDetailsType)
	{
		Destination = CodeDeliveryDetailsType.GetDestination().c_str();
		DeliveryMedium = static_cast<EDeliveryMediumType>(CodeDeliveryDetailsType.GetDeliveryMedium());
		AttributeName = CodeDeliveryDetailsType.GetAttributeName().c_str();
	}
};

UENUM(BlueprintType)
enum CompromisedCredentialsEventActionType
{
	NOT_SET3 UMETA(DisplayName = "NOT_SET"),
	BLOCK1 UMETA(DisplayName = "BLOCK"),
	NO_ACTION1 UMETA(DisplayName = "NO_ACTION")
  };

USTRUCT(BlueprintType)
struct FCompromisedCredentialsActionsType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<CompromisedCredentialsEventActionType> EventAction;

	FCompromisedCredentialsActionsType(){}
	FCompromisedCredentialsActionsType(Aws::CognitoIdentityProvider::Model::CompromisedCredentialsActionsType GetActions)
	{
		EventAction = static_cast<CompromisedCredentialsEventActionType>(GetActions.GetEventAction());
	}
	Aws::CognitoIdentityProvider::Model::CompromisedCredentialsActionsType GetCompromisedCredentialsActionsType()
	{
		Aws::CognitoIdentityProvider::Model::CompromisedCredentialsActionsType CompromisedCredentialsActionsType;
		CompromisedCredentialsActionsType.SetEventAction(static_cast<Aws::CognitoIdentityProvider::Model::CompromisedCredentialsEventActionType>(EventAction.GetValue()));
		return CompromisedCredentialsActionsType;
	}
};

USTRUCT(BlueprintType)
struct FCompromisedCredentialsRiskConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FCompromisedCredentialsActionsType Actions;

	FCompromisedCredentialsRiskConfigurationType(){}
	FCompromisedCredentialsRiskConfigurationType(const Aws::CognitoIdentityProvider::Model::CompromisedCredentialsRiskConfigurationType& CompromisedCredentialsRiskConfiguration)
	{
		Actions = FCompromisedCredentialsActionsType(CompromisedCredentialsRiskConfiguration.GetActions());
	}
	Aws::CognitoIdentityProvider::Model::CompromisedCredentialsRiskConfigurationType ToCompromisedCredentialsRiskConfigurationType()
	{
		Aws::CognitoIdentityProvider::Model::CompromisedCredentialsRiskConfigurationType CompromisedCredentialsRiskConfigurationType;
		CompromisedCredentialsRiskConfigurationType.SetActions(Actions.GetCompromisedCredentialsActionsType());
		return CompromisedCredentialsRiskConfigurationType;
	}
};


USTRUCT(BlueprintType)
struct FAHttpHeader
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString HeaderName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString HeaderValue;

	FAHttpHeader(){}
	FAHttpHeader(const Aws::CognitoIdentityProvider::Model::HttpHeader& HttpHeader)
	{
		HeaderName = HttpHeader.GetHeaderName().c_str();
		HeaderValue = HttpHeader.GetHeaderValue().c_str();
	}
	Aws::CognitoIdentityProvider::Model::HttpHeader ToHttpHeader()
	{
		Aws::CognitoIdentityProvider::Model::HttpHeader HttpHeader;
		HttpHeader.SetHeaderName(TCHAR_TO_UTF8(*HeaderName));
		HttpHeader.SetHeaderValue(TCHAR_TO_UTF8(*HeaderValue));
		return HttpHeader;
	}
	
};

USTRUCT(BlueprintType)
struct FContextDataType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FAHttpHeader> HttpHeaders;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString IpAddress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ServerName;

	FContextDataType(){}

	FContextDataType(const Aws::CognitoIdentityProvider::Model::ContextDataType& ContextDataType)
	{
		for (int i = 0; i < ContextDataType.GetHttpHeaders().size(); i++)
		{
			HttpHeaders.Add(FAHttpHeader(ContextDataType.GetHttpHeaders()[i]));
		}
		IpAddress = ContextDataType.GetIpAddress().c_str();
		ServerName = ContextDataType.GetServerName().c_str();
	}
	Aws::CognitoIdentityProvider::Model::ContextDataType ToContextDataType()
	{
		Aws::CognitoIdentityProvider::Model::ContextDataType ContextDataType;
		for (int i = 0; i < HttpHeaders.Num(); i++)
		{
			ContextDataType.AddHttpHeaders(HttpHeaders[i].ToHttpHeader());
		}
		ContextDataType.SetIpAddress(TCHAR_TO_UTF8(*IpAddress));
		ContextDataType.SetServerName(TCHAR_TO_UTF8(*ServerName));
		return ContextDataType;
	}
};

USTRUCT(BlueprintType)
struct FCustomDomainConfigType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString CertificateArn;

	FCustomDomainConfigType(){}
	FCustomDomainConfigType(const Aws::CognitoIdentityProvider::Model::CustomDomainConfigType& CustomDomainConfigType)
	{
		CertificateArn = CustomDomainConfigType.GetCertificateArn().c_str();
	}
};

UENUM(BlueprintType)
enum ECustomSMSSenderLambdaVersionType
{
	NOT_SET6 UMETA(DisplayName = "NOT_SET"),
	V1_0
  };

USTRUCT(BlueprintType)
struct FCustomEmailLambdaVersionConfigType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<ECustomSMSSenderLambdaVersionType> LambdaVersion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString LambdaArn;
	FCustomEmailLambdaVersionConfigType(){}
	FCustomEmailLambdaVersionConfigType(const Aws::CognitoIdentityProvider::Model::CustomEmailLambdaVersionConfigType& CustomEmailLambdaVersionConfigType)
	{
		LambdaVersion = static_cast<ECustomSMSSenderLambdaVersionType>(CustomEmailLambdaVersionConfigType.GetLambdaVersion());
		LambdaArn = CustomEmailLambdaVersionConfigType.GetLambdaArn().c_str();
	}
};



USTRUCT(BlueprintType)
struct FCustomSMSLambdaVersionConfigType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<ECustomSMSSenderLambdaVersionType> LambdaVersion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString LambdaArn;

	FCustomSMSLambdaVersionConfigType(){}
	FCustomSMSLambdaVersionConfigType(const Aws::CognitoIdentityProvider::Model::CustomSMSLambdaVersionConfigType& CustomSMSLambdaVersionConfigType)
	{
		LambdaVersion = static_cast<ECustomSMSSenderLambdaVersionType>(CustomSMSLambdaVersionConfigType.GetLambdaVersion());
		LambdaArn = CustomSMSLambdaVersionConfigType.GetLambdaArn().c_str();
	}
};


USTRUCT(BlueprintType)
struct FDeviceConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	int32 ChallengeRequiredOnNewDevice;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool DeviceOnlyRememberedOnUserPrompt;

	FDeviceConfigurationType(){}
	FDeviceConfigurationType(const Aws::CognitoIdentityProvider::Model::DeviceConfigurationType& DeviceConfigurationType)
	{
		ChallengeRequiredOnNewDevice = DeviceConfigurationType.GetChallengeRequiredOnNewDevice();
		DeviceOnlyRememberedOnUserPrompt = DeviceConfigurationType.GetDeviceOnlyRememberedOnUserPrompt();
	}
};


USTRUCT(BlueprintType)
struct FDeviceSecretVerifierConfigType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString PasswordVerifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Salt;

	FDeviceSecretVerifierConfigType(){}
	FDeviceSecretVerifierConfigType (const Aws::CognitoIdentityProvider::Model::DeviceSecretVerifierConfigType& DeviceSecretVerifierConfigType)
	{
		PasswordVerifier = DeviceSecretVerifierConfigType.GetPasswordVerifier().c_str();
		Salt = DeviceSecretVerifierConfigType.GetSalt().c_str();
	}
	Aws::CognitoIdentityProvider::Model::DeviceSecretVerifierConfigType ToDeviceSecretVerifierConfigType()
	{
		Aws::CognitoIdentityProvider::Model::DeviceSecretVerifierConfigType DeviceSecretVerifierConfigType;
		DeviceSecretVerifierConfigType.SetPasswordVerifier(TCHAR_TO_UTF8(*PasswordVerifier));
		DeviceSecretVerifierConfigType.SetSalt(TCHAR_TO_UTF8(*Salt));
		return DeviceSecretVerifierConfigType;
	}
	
};

USTRUCT(BlueprintType)
struct FDeviceType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString DeviceKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FAttributeType> DeviceAttributes;

	FDeviceType(){}
	FDeviceType(const Aws::CognitoIdentityProvider::Model::DeviceType& DeviceType)
	{
		DeviceKey = DeviceType.GetDeviceKey().c_str();
		const Aws::Vector<Aws::CognitoIdentityProvider::Model::AttributeType>& DeviceAttributesVector = DeviceType.GetDeviceAttributes();
		for (int i = 0; i < DeviceAttributesVector.size(); i++)
		{
			DeviceAttributes.Add(FAttributeType(DeviceAttributesVector[i]));
		}
	}
};

UENUM(BlueprintType)
enum DomainStatusType
{
	NOT_SET9 UMETA(DisplayName = "NOT_SET"),
	CREATING,
	DELETING,
	UPDATING,
	ACTIVE,
	FAILED
  };

USTRUCT(BlueprintType)
struct FDomainDescriptionType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString UserPoolId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString AWSAccountId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Domain;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString S3Bucket;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString CloudFrontDistribution;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Version;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<DomainStatusType> Status;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FCustomDomainConfigType CustomDomainConfig;

	FDomainDescriptionType(){}
	FDomainDescriptionType(const Aws::CognitoIdentityProvider::Model::DomainDescriptionType& DomainDescriptionType)
	{
		UserPoolId = DomainDescriptionType.GetUserPoolId().c_str();
		AWSAccountId = DomainDescriptionType.GetAWSAccountId().c_str();
		Domain = DomainDescriptionType.GetDomain().c_str();
		S3Bucket = DomainDescriptionType.GetS3Bucket().c_str();
		CloudFrontDistribution = DomainDescriptionType.GetCloudFrontDistribution().c_str();
		Version = DomainDescriptionType.GetVersion().c_str();
		Status = static_cast<DomainStatusType>(DomainDescriptionType.GetStatus());
		CustomDomainConfig = FCustomDomainConfigType(DomainDescriptionType.GetCustomDomainConfig());
	}
};
UENUM(BlueprintType)
enum EEmailSendingAccountType
{
	NOT_SET11 UMETA(DisplayName = "NOT_SET"),
	COGNITO_DEFAULT,
	DEVELOPER
  };

USTRUCT(BlueprintType)
struct FEmailConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString SourceArn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ReplyToEmailAddress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EEmailSendingAccountType> EmailSendingAccount;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString From;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ConfigurationSet;
	
	FEmailConfigurationType(){}
	FEmailConfigurationType(const Aws::CognitoIdentityProvider::Model::EmailConfigurationType& EmailConfigurationType)
	{
		SourceArn = EmailConfigurationType.GetSourceArn().c_str();
		ReplyToEmailAddress = EmailConfigurationType.GetReplyToEmailAddress().c_str();
		EmailSendingAccount = static_cast<EEmailSendingAccountType>(EmailConfigurationType.GetEmailSendingAccount());
		From = EmailConfigurationType.GetFrom().c_str();
		ConfigurationSet = EmailConfigurationType.GetConfigurationSet().c_str();
	}
};

USTRUCT(BlueprintType)
struct FEventContextDataType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString City;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString IpAddress;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Country;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString DeviceName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Timezone;

	FEventContextDataType(){}
	FEventContextDataType(const Aws::CognitoIdentityProvider::Model::EventContextDataType& EventContextDataType)
	{
		City = EventContextDataType.GetCity().c_str();
		IpAddress = EventContextDataType.GetIpAddress().c_str();
		Country = EventContextDataType.GetCountry().c_str();
		DeviceName = EventContextDataType.GetDeviceName().c_str();
		Timezone = EventContextDataType.GetTimezone().c_str();
	}
};

UENUM(BlueprintType)
enum EFeedbackValueType
{
	NOT_SET19 UMETA(DisplayName = "NOT_SET"),
	Valid,
	Invalid
  };


UENUM(BlueprintType)
enum EDeviceRememberedStatus
{
	NOT_SET29 UMETA(DisplayName = "NOT_SET"),
	remembered,
	not_remembered
  };


USTRUCT(BlueprintType)
struct FEventFeedbackType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EFeedbackValueType> FeedbackValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime FeedbackDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Provider;

	FEventFeedbackType(){}
	FEventFeedbackType(const Aws::CognitoIdentityProvider::Model::EventFeedbackType& EventFeedbackType)
	{
		FeedbackValue = static_cast<EFeedbackValueType>(EventFeedbackType.GetFeedbackValue());
		const Aws::Utils::DateTime& awsDateTime = EventFeedbackType.GetFeedbackDate();
		FeedbackDate = FDateTime(
			awsDateTime.GetYear(),
			(int)awsDateTime.GetMonth() + 1,
			awsDateTime.GetDay(),
			awsDateTime.GetHour(),
			awsDateTime.GetMinute(),
			awsDateTime.GetSecond(),
			awsDateTime.Millis()
		);
		Provider = EventFeedbackType.GetProvider().c_str();
	}
};



USTRUCT(BlueprintType)
struct FGroupType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString GroupName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString UserPoolId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Description;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString RoleArn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	int32 Precedence;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime LastModifiedDate;
	
	FGroupType(){}
	FGroupType(const Aws::CognitoIdentityProvider::Model::GroupType& GroupType)
	{
		GroupName = GroupType.GetGroupName().c_str();
		UserPoolId = GroupType.GetUserPoolId().c_str();
		Description = GroupType.GetDescription().c_str();
		RoleArn = GroupType.GetRoleArn().c_str();
		Precedence = GroupType.GetPrecedence();
		const Aws::Utils::DateTime& awsDateTime = GroupType.GetLastModifiedDate();
		LastModifiedDate = FDateTime(
			awsDateTime.GetYear(),
			(int)awsDateTime.GetMonth() + 1,
			awsDateTime.GetDay(),
			awsDateTime.GetHour(),
			awsDateTime.GetMinute(),
			awsDateTime.GetSecond(),
			awsDateTime.Millis()
		);
	}
};


USTRUCT(BlueprintType)
struct FLambdaConfigType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString CustomMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString PreSignUp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString PostConfirmation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString PreAuthentication;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString PostAuthentication;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString DefineAuthChallenge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString CreateAuthChallenge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString VerifyAuthChallengeResponse;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString PreTokenGeneration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString UserMigration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FCustomSMSLambdaVersionConfigType CustomSMSSender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FCustomEmailLambdaVersionConfigType CustomEmailSender;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString KMSKeyID;
	FLambdaConfigType(){}
	FLambdaConfigType(const Aws::CognitoIdentityProvider::Model::LambdaConfigType& LambdaConfigType)
	{
		CustomMessage = LambdaConfigType.GetCustomMessage().c_str();
		PreSignUp = LambdaConfigType.GetPreSignUp().c_str();
		PostConfirmation = LambdaConfigType.GetPostConfirmation().c_str();
		PreAuthentication = LambdaConfigType.GetPreAuthentication().c_str();
		PostAuthentication = LambdaConfigType.GetPostAuthentication().c_str();
		DefineAuthChallenge = LambdaConfigType.GetDefineAuthChallenge().c_str();
		CreateAuthChallenge = LambdaConfigType.GetCreateAuthChallenge().c_str();
		VerifyAuthChallengeResponse = LambdaConfigType.GetVerifyAuthChallengeResponse().c_str();
		PreTokenGeneration = LambdaConfigType.GetPreTokenGeneration().c_str();
		UserMigration = LambdaConfigType.GetUserMigration().c_str();
		CustomSMSSender = FCustomSMSLambdaVersionConfigType(LambdaConfigType.GetCustomSMSSender());
		CustomEmailSender = FCustomEmailLambdaVersionConfigType(LambdaConfigType.GetCustomEmailSender());
		KMSKeyID = LambdaConfigType.GetKMSKeyID().c_str();
	}
	

	// Add more properties as needed.
};

UENUM(BlueprintType)
enum ELogLevel
{
	NOT_SET21 UMETA(DisplayName = "NOT_SET"),
	ERROR_
  };

UENUM(BlueprintType)
enum EEventSourceName
{
	NOT_SET22 UMETA(DisplayName = "NOT_SET"),
	userNotification
  };

USTRUCT(BlueprintType)
struct FLogConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<ELogLevel> LogLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EEventSourceName> EventSource;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FCloudWatchLogsConfigurationType CloudWatchLogsConfiguration;

	FLogConfigurationType(){}
	FLogConfigurationType(const Aws::CognitoIdentityProvider::Model::LogConfigurationType& LogConfigurationType)
	{
		LogLevel = static_cast<ELogLevel>(LogConfigurationType.GetLogLevel());
		EventSource = static_cast<EEventSourceName>(LogConfigurationType.GetEventSource());
		CloudWatchLogsConfiguration = FCloudWatchLogsConfigurationType(LogConfigurationType.GetCloudWatchLogsConfiguration());
	}
	Aws::CognitoIdentityProvider::Model::LogConfigurationType ToLogConfigurationType()
	{
		Aws::CognitoIdentityProvider::Model::LogConfigurationType LogConfigurationType;
		LogConfigurationType.SetLogLevel(static_cast<Aws::CognitoIdentityProvider::Model::LogLevel>(LogLevel.GetValue()));
		LogConfigurationType.SetEventSource(static_cast<Aws::CognitoIdentityProvider::Model::EventSourceName>(EventSource.GetValue()));
		LogConfigurationType.SetCloudWatchLogsConfiguration(CloudWatchLogsConfiguration.ToCloudWatchLogsConfigurationType());
		return LogConfigurationType;
	}
};

USTRUCT(BlueprintType)
struct FLogDeliveryConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FLogConfigurationType> LogConfigurations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString UserPoolID;

	FLogDeliveryConfigurationType(){}
	FLogDeliveryConfigurationType(const Aws::CognitoIdentityProvider::Model::LogDeliveryConfigurationType& LogDeliveryConfigurationType)
	{
		for (int i = 0; i < LogDeliveryConfigurationType.GetLogConfigurations().size(); i++)
		{
			LogConfigurations.Add(FLogConfigurationType(LogDeliveryConfigurationType.GetLogConfigurations()[i]));
		}
		UserPoolID = LogDeliveryConfigurationType.GetUserPoolId().c_str();
	}
};

USTRUCT(BlueprintType)
struct FMessageTemplateType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString SMSMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString EmailMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString EmailSubject;

	FMessageTemplateType(){}
	FMessageTemplateType(const Aws::CognitoIdentityProvider::Model::MessageTemplateType& MessageTemplateType)
	{
		SMSMessage = MessageTemplateType.GetSMSMessage().c_str();
		EmailMessage = MessageTemplateType.GetEmailMessage().c_str();
		EmailSubject = MessageTemplateType.GetEmailSubject().c_str();
	}
	Aws::CognitoIdentityProvider::Model::MessageTemplateType ToMessageTemplateType()
	{
		Aws::CognitoIdentityProvider::Model::MessageTemplateType MessageTemplateType;
		MessageTemplateType.SetSMSMessage(TCHAR_TO_UTF8(*SMSMessage));
		MessageTemplateType.SetEmailMessage(TCHAR_TO_UTF8(*EmailMessage));
		MessageTemplateType.SetEmailSubject(TCHAR_TO_UTF8(*EmailSubject));
		return MessageTemplateType;
	}
};

USTRUCT(BlueprintType)
struct FMFAOptionType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString AttributeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EDeliveryMediumType> DeliveryMedium;

	FMFAOptionType(){}
	FMFAOptionType(const Aws::CognitoIdentityProvider::Model::MFAOptionType& MFAOptionType)
	{
		DeliveryMedium = static_cast<EDeliveryMediumType>(MFAOptionType.GetDeliveryMedium());
		AttributeName = MFAOptionType.GetAttributeName().c_str();
	}
	Aws::CognitoIdentityProvider::Model::MFAOptionType ToMFAOptionType()
	{
		Aws::CognitoIdentityProvider::Model::MFAOptionType MFAOptionType;
		MFAOptionType.SetDeliveryMedium(static_cast<Aws::CognitoIdentityProvider::Model::DeliveryMediumType>(DeliveryMedium.GetValue()));
		MFAOptionType.SetAttributeName(TCHAR_TO_UTF8(*AttributeName));
		return MFAOptionType;
	}
};



USTRUCT(BlueprintType)
struct FNotifyEmailType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Subject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString HtmlBody;

	FNotifyEmailType(){}
	FNotifyEmailType(const Aws::CognitoIdentityProvider::Model::NotifyEmailType& NotifyEmailType)
	{
		Subject = NotifyEmailType.GetSubject().c_str();
		HtmlBody = NotifyEmailType.GetHtmlBody().c_str();
	}
	Aws::CognitoIdentityProvider::Model::NotifyEmailType ToNotifyEmailType()
	{
		Aws::CognitoIdentityProvider::Model::NotifyEmailType NotifyEmailType;
		NotifyEmailType.SetSubject(TCHAR_TO_UTF8(*Subject));
		NotifyEmailType.SetHtmlBody(TCHAR_TO_UTF8(*HtmlBody));
		return NotifyEmailType;
	}
};


USTRUCT(BlueprintType)
struct FNotifyConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString SourceArn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FNotifyEmailType BlockEmail;

	// Add more properties as needed.
	FNotifyConfigurationType(){}
	FNotifyConfigurationType(const Aws::CognitoIdentityProvider::Model::NotifyConfigurationType& NotifyConfiguration)
	{
		SourceArn = NotifyConfiguration.GetSourceArn().c_str();
		BlockEmail = NotifyConfiguration.GetBlockEmail();
	}
	Aws::CognitoIdentityProvider::Model::NotifyConfigurationType ToNotifyConfigurationType()
	{
		Aws::CognitoIdentityProvider::Model::NotifyConfigurationType NotifyConfigurationType;
		NotifyConfigurationType.SetSourceArn(TCHAR_TO_UTF8(*SourceArn));
		NotifyConfigurationType.SetBlockEmail(BlockEmail.ToNotifyEmailType());
		return NotifyConfigurationType;
	}
};



USTRUCT(BlueprintType)
struct FNumberAttributeConstraintsType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString MinValue;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString MaxValue;

	FNumberAttributeConstraintsType(){}
	FNumberAttributeConstraintsType (const Aws::CognitoIdentityProvider::Model::NumberAttributeConstraintsType& NumberAttributeConstraintsType)
	{
		MinValue = NumberAttributeConstraintsType.GetMinValue().c_str();
		MaxValue = NumberAttributeConstraintsType.GetMaxValue().c_str();
	}

	Aws::CognitoIdentityProvider::Model::NumberAttributeConstraintsType ToNumberAttributeConstraintsType()
	{
		Aws::CognitoIdentityProvider::Model::NumberAttributeConstraintsType NumberAttributeConstraintsType;
		NumberAttributeConstraintsType.SetMinValue(TCHAR_TO_UTF8(*MinValue));
		NumberAttributeConstraintsType.SetMaxValue(TCHAR_TO_UTF8(*MaxValue));
		return NumberAttributeConstraintsType;
	}
	
};

USTRUCT(BlueprintType)
struct FAccountTakeoverRiskConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FNotifyConfigurationType NotifyConfiguration;  // Assuming NotifyConfigurationType is another custom struct.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FAccountTakeoverActionsType Actions;  // Assuming AccountTakeoverActionsType is defined as per your previous structure.

	FAccountTakeoverRiskConfigurationType(){}
	FAccountTakeoverRiskConfigurationType(const Aws::CognitoIdentityProvider::Model::AccountTakeoverRiskConfigurationType& AccountTakeoverRiskConfigurationType)
	{
		NotifyConfiguration = FNotifyConfigurationType(AccountTakeoverRiskConfigurationType.GetNotifyConfiguration());
		Actions = FAccountTakeoverActionsType(AccountTakeoverRiskConfigurationType.GetActions());
	}

	Aws::CognitoIdentityProvider::Model::AccountTakeoverRiskConfigurationType ToAccountTakeoverRiskConfigurationType()
	{
		Aws::CognitoIdentityProvider::Model::AccountTakeoverRiskConfigurationType AccountTakeoverRiskConfigurationType;
		AccountTakeoverRiskConfigurationType.SetNotifyConfiguration(NotifyConfiguration.ToNotifyConfigurationType());
		AccountTakeoverRiskConfigurationType.SetActions(Actions.ToAccountTakeoverActionsType());
		return AccountTakeoverRiskConfigurationType;
	}
	
};

USTRUCT(BlueprintType)
struct FPasswordPolicyType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	int32 MinimumLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool RequireUppercase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool RequireNumbers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool RequireSymbols;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool RequireLowercase;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	int32 TemporaryPasswordValidityDays;

	FPasswordPolicyType(){}
	FPasswordPolicyType(const Aws::CognitoIdentityProvider::Model::PasswordPolicyType& PasswordPolicyType)
	{
		MinimumLength = PasswordPolicyType.GetMinimumLength();
		RequireUppercase = PasswordPolicyType.GetRequireUppercase();
		RequireNumbers = PasswordPolicyType.GetRequireNumbers();
		RequireSymbols = PasswordPolicyType.GetRequireSymbols();
		RequireLowercase = PasswordPolicyType.GetRequireLowercase();
		TemporaryPasswordValidityDays = PasswordPolicyType.GetTemporaryPasswordValidityDays();
	}
};

UENUM(BlueprintType)
enum EIdentityProviderType
{
	NOT_SET1 UMETA(DisplayName = "NOT_SET"),
	SAML,
	Facebook,
	Google,
	LoginWithAmazon,
	SignInWithApple,
	OIDC
  };

USTRUCT(BlueprintType)
struct FProviderDescription
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ProviderName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EIdentityProviderType> ProviderType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime CreationDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime LastModifiedDate;

	FProviderDescription(){}
	FProviderDescription(const Aws::CognitoIdentityProvider::Model::ProviderDescription& ProviderDescription)
	{
		ProviderName = ProviderDescription.GetProviderName().c_str();
		ProviderType = static_cast<EIdentityProviderType>(ProviderDescription.GetProviderType());
		const Aws::Utils::DateTime& awsDateTime = ProviderDescription.GetCreationDate();
		CreationDate = FDateTime(
			awsDateTime.GetYear(),
			(int)awsDateTime.GetMonth() + 1,
			awsDateTime.GetDay(),
			awsDateTime.GetHour(),
			awsDateTime.GetMinute(),
			awsDateTime.GetSecond(),
			awsDateTime.Millis()
		);

		const Aws::Utils::DateTime& awsLastModified = ProviderDescription.GetLastModifiedDate();
		LastModifiedDate = FDateTime(
			awsLastModified.GetYear(),
			(int)awsLastModified.GetMonth() + 1,
			awsLastModified.GetDay(),
			awsLastModified.GetHour(),
			awsLastModified.GetMinute(),
			awsLastModified.GetSecond(),
			awsLastModified.Millis()
		);
	}
};

USTRUCT(BlueprintType)
struct FProviderUserIdentifierType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ProviderName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ProviderAttributeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ProviderAttributeValue;

	FProviderUserIdentifierType(){}
	FProviderUserIdentifierType(const Aws::CognitoIdentityProvider::Model::ProviderUserIdentifierType& ProviderUserIdentifierType)
	{
		ProviderName = ProviderUserIdentifierType.GetProviderName().c_str();
		ProviderAttributeName = ProviderUserIdentifierType.GetProviderAttributeName().c_str();
		ProviderAttributeValue = ProviderUserIdentifierType.GetProviderAttributeValue().c_str();
	}
	Aws::CognitoIdentityProvider::Model::ProviderUserIdentifierType ToProviderUserIdentifierType()
	{
		Aws::CognitoIdentityProvider::Model::ProviderUserIdentifierType ProviderUserIdentifierType;
		ProviderUserIdentifierType.SetProviderName(TCHAR_TO_UTF8(*ProviderName));
		ProviderUserIdentifierType.SetProviderAttributeName(TCHAR_TO_UTF8(*ProviderAttributeName));
		ProviderUserIdentifierType.SetProviderAttributeValue(TCHAR_TO_UTF8(*ProviderAttributeValue));
		return ProviderUserIdentifierType;
	}
};

UENUM(BlueprintType)
enum ERecoveryOptionNameType
{
	NOT_SET2 UMETA(DisplayName = "NOT_SET"),
	verified_email,
	verified_phone_number,
	admin_only
  };

USTRUCT(BlueprintType)
struct FRecoveryOptionType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<ERecoveryOptionNameType> Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	int32 Priority;

	FRecoveryOptionType(){}
	FRecoveryOptionType(const Aws::CognitoIdentityProvider::Model::RecoveryOptionType& RecoveryOptionType)
		: Name(static_cast<ERecoveryOptionNameType>(RecoveryOptionType.GetName())),
		Priority(RecoveryOptionType.GetPriority())
	{
	}
	Aws::CognitoIdentityProvider::Model::RecoveryOptionType ToRecoveryOptionType()
	{
		Aws::CognitoIdentityProvider::Model::RecoveryOptionType RecoveryOptionType;
		RecoveryOptionType.SetName(static_cast<Aws::CognitoIdentityProvider::Model::RecoveryOptionNameType>(Name.GetValue()));
		RecoveryOptionType.SetPriority(Priority);
		return RecoveryOptionType;
	}
};

USTRUCT(BlueprintType)
struct FResourceServerScopeType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ScopeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ScopeDescription;

	FResourceServerScopeType(){}
	FResourceServerScopeType(const Aws::CognitoIdentityProvider::Model::ResourceServerScopeType& ResourceServerScopeType)
	{
		ScopeName = ResourceServerScopeType.GetScopeName().c_str();
		ScopeDescription = ResourceServerScopeType.GetScopeDescription().c_str();
	}
	Aws::CognitoIdentityProvider::Model::ResourceServerScopeType ToResourceServerScopeType()
	{
		Aws::CognitoIdentityProvider::Model::ResourceServerScopeType ResourceServerScopeType;
		ResourceServerScopeType.SetScopeName(TCHAR_TO_UTF8(*ScopeName));
		ResourceServerScopeType.SetScopeDescription(TCHAR_TO_UTF8(*ScopeDescription));
		return ResourceServerScopeType;
	}
};

USTRUCT(BlueprintType)
struct FResourceServerType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString UserPoolId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Identifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FResourceServerScopeType> Scopes;

	FResourceServerType(){}
	FResourceServerType(const Aws::CognitoIdentityProvider::Model::ResourceServerType& ResourceServerType)
	{
		UserPoolId = ResourceServerType.GetUserPoolId().c_str();
		Identifier = ResourceServerType.GetIdentifier().c_str();
		Name = ResourceServerType.GetName().c_str();
		for (auto Scope : ResourceServerType.GetScopes())
		{
			Scopes.Add(FResourceServerScopeType(Scope));
		}
	}

};



USTRUCT(BlueprintType)
struct FAccountRecoverySettingType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FRecoveryOptionType> RecoveryMechanisms;

	FAccountRecoverySettingType(){}
	FAccountRecoverySettingType(const Aws::CognitoIdentityProvider::Model::AccountRecoverySettingType& AccountRecoverySettingType)
	{
		for (auto RecoveryMechanism : AccountRecoverySettingType.GetRecoveryMechanisms())
		{
			RecoveryMechanisms.Add(FRecoveryOptionType(RecoveryMechanism));
		}
	}
	Aws::CognitoIdentityProvider::Model::AccountRecoverySettingType ToAccountRecoverySettingType()
	{
		Aws::CognitoIdentityProvider::Model::AccountRecoverySettingType AccountRecoverySettingType;
		for (auto RecoveryMechanism : RecoveryMechanisms)
		{
			AccountRecoverySettingType.AddRecoveryMechanisms(RecoveryMechanism.ToRecoveryOptionType());
		}
		return AccountRecoverySettingType;
	}
	
};

USTRUCT(BlueprintType)
struct FRiskExceptionConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FString> BlockedIPRange;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FString> SkippedIPRange;

	FRiskExceptionConfigurationType(){}
	FRiskExceptionConfigurationType(const Aws::CognitoIdentityProvider::Model::RiskExceptionConfigurationType& RiskExceptionConfigurationType)
	{
		for(auto BlockedIPRangeVal : RiskExceptionConfigurationType.GetBlockedIPRangeList())
		{
			BlockedIPRange.Add(BlockedIPRangeVal.c_str());
		}
		for(auto SkippedIPRangeVal : RiskExceptionConfigurationType.GetSkippedIPRangeList())
		{
			SkippedIPRange.Add(SkippedIPRangeVal.c_str());
		}
	}
	Aws::CognitoIdentityProvider::Model::RiskExceptionConfigurationType ToRiskExceptionConfigurationType()
	{
		Aws::CognitoIdentityProvider::Model::RiskExceptionConfigurationType RiskExceptionConfigurationType;
		for(auto BlockedIPRangeVal : BlockedIPRange)
		{
			RiskExceptionConfigurationType.AddBlockedIPRangeList(TCHAR_TO_UTF8(*BlockedIPRangeVal));
		}
		for(auto SkippedIPRangeVal : SkippedIPRange)
		{
			RiskExceptionConfigurationType.AddSkippedIPRangeList(TCHAR_TO_UTF8(*SkippedIPRangeVal));
		}
		return RiskExceptionConfigurationType;
	}
};

UENUM(BlueprintType)
enum EAttributeDataType1
{
	NOT_SET12 UMETA(DisplayName = "NOT_SET"),
	String,
	Number,
	DateTime,
	Boolean
  };


USTRUCT(BlueprintType)
struct FStringAttributeConstraintsType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString MinLength;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString MaxLength;

	FStringAttributeConstraintsType(){}
	FStringAttributeConstraintsType(const Aws::CognitoIdentityProvider::Model::StringAttributeConstraintsType& StringAttributeConstraintsType)
	{
		MinLength = StringAttributeConstraintsType.GetMinLength().c_str();
		MaxLength = StringAttributeConstraintsType.GetMaxLength().c_str();
	}
	Aws::CognitoIdentityProvider::Model::StringAttributeConstraintsType ToStringAttributeConstraintsType()
	{
		Aws::CognitoIdentityProvider::Model::StringAttributeConstraintsType StringAttributeConstraintsType;
		StringAttributeConstraintsType.SetMinLength(TCHAR_TO_UTF8(*MinLength));
		StringAttributeConstraintsType.SetMaxLength(TCHAR_TO_UTF8(*MaxLength));
		return StringAttributeConstraintsType;
	}
};

USTRUCT(BlueprintType)
struct FSchemaAttributeType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EAttributeDataType1> AttributeDataType;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool Mutable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool Required;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FNumberAttributeConstraintsType NumberAttributeConstraints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FStringAttributeConstraintsType StringAttributeConstraints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool DeveloperOnlyAttribute;
	
	FSchemaAttributeType(){}
	FSchemaAttributeType(const Aws::CognitoIdentityProvider::Model::SchemaAttributeType& SchemaAttributeType)
	{
		Name = SchemaAttributeType.GetName().c_str();
		AttributeDataType = static_cast<EAttributeDataType1>(SchemaAttributeType.GetAttributeDataType());
		Mutable = SchemaAttributeType.GetMutable();
		Required = SchemaAttributeType.GetRequired();
		NumberAttributeConstraints = FNumberAttributeConstraintsType(SchemaAttributeType.GetNumberAttributeConstraints());
		StringAttributeConstraints = FStringAttributeConstraintsType(SchemaAttributeType.GetStringAttributeConstraints());
		DeveloperOnlyAttribute = SchemaAttributeType.GetDeveloperOnlyAttribute();
	}
	Aws::CognitoIdentityProvider::Model::SchemaAttributeType ToSchemaAttributeType()
	{
		Aws::CognitoIdentityProvider::Model::SchemaAttributeType SchemaAttributeType;
		SchemaAttributeType.SetName(TCHAR_TO_UTF8(*Name));
		SchemaAttributeType.SetAttributeDataType(static_cast<Aws::CognitoIdentityProvider::Model::AttributeDataType>(AttributeDataType.GetValue()));
		SchemaAttributeType.SetMutable(Mutable);
		SchemaAttributeType.SetRequired(Required);
		SchemaAttributeType.SetNumberAttributeConstraints(NumberAttributeConstraints.ToNumberAttributeConstraintsType());
		SchemaAttributeType.SetStringAttributeConstraints(StringAttributeConstraints.ToStringAttributeConstraintsType());
		SchemaAttributeType.SetDeveloperOnlyAttribute(DeveloperOnlyAttribute);
		return SchemaAttributeType;
	}
};

USTRUCT(BlueprintType)
struct FSmsConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ExternalId;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString SnsCallerArn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString SnsRegion;

	FSmsConfigurationType(){}
	FSmsConfigurationType(const Aws::CognitoIdentityProvider::Model::SmsConfigurationType& SmsConfigurationType)
	{
		ExternalId = SmsConfigurationType.GetExternalId().c_str();
		SnsCallerArn = SmsConfigurationType.GetSnsCallerArn().c_str();
		SnsRegion = SmsConfigurationType.GetSnsRegion().c_str();		
	}
	Aws::CognitoIdentityProvider::Model::SmsConfigurationType ToSmsConfigurationType()
	{
		Aws::CognitoIdentityProvider::Model::SmsConfigurationType SmsConfigurationType;
		SmsConfigurationType.SetExternalId(TCHAR_TO_UTF8(*ExternalId));
		SmsConfigurationType.SetSnsCallerArn(TCHAR_TO_UTF8(*SnsCallerArn));
		SmsConfigurationType.SetSnsRegion(TCHAR_TO_UTF8(*SnsRegion));
		return SmsConfigurationType;
	}
};

USTRUCT(BlueprintType)
struct FSmsMfaConfigType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FSmsConfigurationType SmsMfaSettings;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString SmsAuthenticationMessage;

	FSmsMfaConfigType(){}
	FSmsMfaConfigType(const Aws::CognitoIdentityProvider::Model::SmsMfaConfigType& SmsMfaConfigType)
	{
		SmsMfaSettings = SmsMfaConfigType.GetSmsConfiguration();
		SmsAuthenticationMessage = SmsMfaConfigType.GetSmsAuthenticationMessage().c_str();
	}
	Aws::CognitoIdentityProvider::Model::SmsMfaConfigType ToSmsMfaConfigType()
	{
		Aws::CognitoIdentityProvider::Model::SmsMfaConfigType SmsMfaConfigType;
		SmsMfaConfigType.SetSmsConfiguration(SmsMfaSettings.ToSmsConfigurationType());
		SmsMfaConfigType.SetSmsAuthenticationMessage(TCHAR_TO_UTF8(*SmsAuthenticationMessage));
		return SmsMfaConfigType;
	}
};

USTRUCT(BlueprintType)
struct FSMSMfaSettingsType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool Enabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool PreferredMfa;
	FSMSMfaSettingsType(){}
	FSMSMfaSettingsType(const Aws::CognitoIdentityProvider::Model::SMSMfaSettingsType& SMSMfaSettingsType)
	{
		Enabled = SMSMfaSettingsType.GetEnabled();
		PreferredMfa = SMSMfaSettingsType.GetPreferredMfa();
	}
	Aws::CognitoIdentityProvider::Model::SMSMfaSettingsType ToSMSMfaSettingsType()
	{
		Aws::CognitoIdentityProvider::Model::SMSMfaSettingsType SMSMfaSettingsType;
		SMSMfaSettingsType.SetEnabled(Enabled);
		SMSMfaSettingsType.SetPreferredMfa(PreferredMfa);
		return SMSMfaSettingsType;
	}
};

USTRUCT(BlueprintType)
struct FSoftwareTokenMfaConfigType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool Enabled;

	FSoftwareTokenMfaConfigType(){}
	FSoftwareTokenMfaConfigType(const Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaConfigType& SoftwareTokenMfaConfigType)
	{
		Enabled = SoftwareTokenMfaConfigType.GetEnabled();
	}
	Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaConfigType ToSoftwareTokenMfaConfigType()
	{
		Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaConfigType SoftwareTokenMfaConfigType;
		SoftwareTokenMfaConfigType.SetEnabled(Enabled);
		return SoftwareTokenMfaConfigType;
	}
};

USTRUCT(BlueprintType)
struct FSoftwareTokenMfaSettingsType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool Enabled;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool PreferredMfa;

	FSoftwareTokenMfaSettingsType(){}
	FSoftwareTokenMfaSettingsType(const Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaSettingsType& SoftwareTokenMfaSettingsType)
	{
		Enabled = SoftwareTokenMfaSettingsType.GetEnabled();
		PreferredMfa = SoftwareTokenMfaSettingsType.GetPreferredMfa();
	}
	Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaSettingsType ToSoftwareTokenMfaSettingsType()
	{
		Aws::CognitoIdentityProvider::Model::SoftwareTokenMfaSettingsType SoftwareTokenMfaSettingsType;
		SoftwareTokenMfaSettingsType.SetEnabled(Enabled);
		SoftwareTokenMfaSettingsType.SetPreferredMfa(PreferredMfa);
		return SoftwareTokenMfaSettingsType;
	}
};

USTRUCT(BlueprintType)
struct FAdminCreateUserConfigType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool AllowAdminCreateUserOnly;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	int32 UnusedAccountValidityDays;  // Assuming this is a string or change type as needed.

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FMessageTemplateType InviteMessageTemplate;  // Assuming MessageTemplateType is another custom struct.

	FAdminCreateUserConfigType(){}
	FAdminCreateUserConfigType(const Aws::CognitoIdentityProvider::Model::AdminCreateUserConfigType& AdminCreateUserConfigType)
	{
		AllowAdminCreateUserOnly = AdminCreateUserConfigType.GetAllowAdminCreateUserOnly();
		UnusedAccountValidityDays = AdminCreateUserConfigType.GetUnusedAccountValidityDays();
		InviteMessageTemplate = FMessageTemplateType(AdminCreateUserConfigType.GetInviteMessageTemplate());
	}
	Aws::CognitoIdentityProvider::Model::AdminCreateUserConfigType ToAdminCreateUserConfigType()
	{
		Aws::CognitoIdentityProvider::Model::AdminCreateUserConfigType AdminCreateUserConfigType;
		AdminCreateUserConfigType.SetAllowAdminCreateUserOnly(AllowAdminCreateUserOnly);
		AdminCreateUserConfigType.SetUnusedAccountValidityDays(UnusedAccountValidityDays);
		AdminCreateUserConfigType.SetInviteMessageTemplate(InviteMessageTemplate.ToMessageTemplateType());
		return AdminCreateUserConfigType;
	}
};



USTRUCT(BlueprintType)
struct FTokenValidityUnitsType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString AccessToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString IdToken;

	// Add more properties as needed.
};

USTRUCT(BlueprintType)
struct FUICustomizationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ClientID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime CreationDate;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Kit")
	FDateTime LastModifiedDate;
	
	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Kit")
	FString CSS;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Kit")
	FString ImageURL;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Kit")
	FString CSSVersion;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Kit")
	FString UserPoolID;

	FUICustomizationType(){}
	FUICustomizationType(const Aws::CognitoIdentityProvider::Model::UICustomizationType& UICustomizationType)
	{
		ClientID = UICustomizationType.GetClientId().c_str();
		const Aws::Utils::DateTime& awsDateTime = UICustomizationType.GetCreationDate();
		CreationDate = FDateTime(
			awsDateTime.GetYear(),
			(int)awsDateTime.GetMonth() + 1,
			awsDateTime.GetDay(),
			awsDateTime.GetHour(),
			awsDateTime.GetMinute(),
			awsDateTime.GetSecond(),
			awsDateTime.Millis()
		);

		const Aws::Utils::DateTime& awsLastModified = UICustomizationType.GetLastModifiedDate();
		LastModifiedDate = FDateTime(
			awsLastModified.GetYear(),
			(int)awsLastModified.GetMonth() + 1,
			awsLastModified.GetDay(),
			awsLastModified.GetHour(),
			awsLastModified.GetMinute(),
			awsLastModified.GetSecond(),
			awsLastModified.Millis()
		);
		CSS = UICustomizationType.GetCSS().c_str();
		ImageURL = UICustomizationType.GetImageUrl().c_str();
		CSSVersion = UICustomizationType.GetCSSVersion().c_str();
		UserPoolID = UICustomizationType.GetUserPoolId().c_str();
	}
};

USTRUCT(BlueprintType)
struct FUserAttributeUpdateSettingsType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool Enabled;

	FUserAttributeUpdateSettingsType(){}
};

USTRUCT(BlueprintType)
struct FUserContextDataType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString EncodedData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString IpAddress;

	FUserContextDataType(){}
	FUserContextDataType(const Aws::CognitoIdentityProvider::Model::UserContextDataType& UserContextDataType)
	{
		EncodedData = UserContextDataType.GetEncodedData().c_str();
		IpAddress = UserContextDataType.GetIpAddress().c_str();
	}
	Aws::CognitoIdentityProvider::Model::UserContextDataType ToUserContextDataType()
	{
		Aws::CognitoIdentityProvider::Model::UserContextDataType UserContextDataType;
		UserContextDataType.SetEncodedData(TCHAR_TO_UTF8(*EncodedData));
		UserContextDataType.SetIpAddress(TCHAR_TO_UTF8(*IpAddress));
		return UserContextDataType;
	}
};

USTRUCT(BlueprintType)
struct FUserImportJobType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString JobId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString PreSignedUrl;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString CloudWatchLogsRoleArn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime CreationDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime StartDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime CompletionDate;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	int32 ImportedUsers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	int32 SkippedUsers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	int32 FailedUsers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString CompletionMessage;

	FUserImportJobType(){}
	FUserImportJobType(const Aws::CognitoIdentityProvider::Model::UserImportJobType& UserImportJobType)
	{
		JobId = UserImportJobType.GetJobId().c_str();
		PreSignedUrl = UserImportJobType.GetPreSignedUrl().c_str();
		CloudWatchLogsRoleArn = UserImportJobType.GetCloudWatchLogsRoleArn().c_str();
		const Aws::Utils::DateTime& awsDateTime = UserImportJobType.GetCreationDate();
		CreationDate = FDateTime(
			awsDateTime.GetYear(),
			(int)awsDateTime.GetMonth() + 1,
			awsDateTime.GetDay(),
			awsDateTime.GetHour(),
			awsDateTime.GetMinute(),
			awsDateTime.GetSecond(),
			awsDateTime.Millis()
		);
		const Aws::Utils::DateTime& awsDateTime2 = UserImportJobType.GetStartDate();
		StartDate = FDateTime(
			awsDateTime2.GetYear(),
			(int)awsDateTime2.GetMonth() + 1,
			awsDateTime2.GetDay(),
			awsDateTime2.GetHour(),
			awsDateTime2.GetMinute(),
			awsDateTime2.GetSecond(),
			awsDateTime2.Millis()
		);
		const Aws::Utils::DateTime& awsDateTime3 = UserImportJobType.GetCompletionDate();
		CompletionDate = FDateTime(
			awsDateTime3.GetYear(),
			(int)awsDateTime3.GetMonth() + 1,
			awsDateTime3.GetDay(),
			awsDateTime3.GetHour(),
			awsDateTime3.GetMinute(),
			awsDateTime3.GetSecond(),
			awsDateTime3.Millis()
		);
		ImportedUsers = UserImportJobType.GetImportedUsers();
		SkippedUsers = UserImportJobType.GetSkippedUsers();
		FailedUsers = UserImportJobType.GetFailedUsers();
		CompletionMessage = UserImportJobType.GetCompletionMessage().c_str();
	}
	Aws::CognitoIdentityProvider::Model::UserImportJobType ToUserImportJobType()
	{
		Aws::CognitoIdentityProvider::Model::UserImportJobType UserImportJobType;
		UserImportJobType.SetJobId(TCHAR_TO_UTF8(*JobId));
		UserImportJobType.SetPreSignedUrl(TCHAR_TO_UTF8(*PreSignedUrl));
		return UserImportJobType;
	}
};

USTRUCT(BlueprintType)
struct FUsernameConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString CaseSensitive;

	// Add more properties as needed.
};

USTRUCT(BlueprintType)
struct FUserPoolAddOnsType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString AdvancedSecurityMode;

	// Add more properties as needed.
};

USTRUCT(BlueprintType)
struct FUserPoolClientDescription
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ClientName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ClientId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString UserPoolId;

	FUserPoolClientDescription(){}
	FUserPoolClientDescription(const Aws::CognitoIdentityProvider::Model::UserPoolClientDescription& UserPoolClientDescription)
	{
		ClientName = UserPoolClientDescription.GetClientName().c_str();
		ClientId = UserPoolClientDescription.GetClientId().c_str();
		UserPoolId = UserPoolClientDescription.GetUserPoolId().c_str();
	}
};

USTRUCT(BlueprintType)
struct FUserPoolClientType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ClientId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ClientName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FAnalyticsConfigurationType AnalyticsConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime CreationDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime LastModifiedDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString UserPoolId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FString> CallbackURLs;
	

	FUserPoolClientType(){}
	FUserPoolClientType(const Aws::CognitoIdentityProvider::Model::UserPoolClientType& UserPoolClientType)
	{
		ClientId = UserPoolClientType.GetClientId().c_str();
		ClientName = UserPoolClientType.GetClientName().c_str();
		AnalyticsConfiguration = UserPoolClientType.GetAnalyticsConfiguration();
		const Aws::Utils::DateTime& awsDateTime = UserPoolClientType.GetCreationDate();
		CreationDate = FDateTime(
			awsDateTime.GetYear(),
			(int)awsDateTime.GetMonth() + 1,
			awsDateTime.GetDay(),
			awsDateTime.GetHour(),
			awsDateTime.GetMinute(),
			awsDateTime.GetSecond(),
			awsDateTime.Millis()
		);
		const Aws::Utils::DateTime& awsDateTime2 = UserPoolClientType.GetLastModifiedDate();
		LastModifiedDate = FDateTime(
			awsDateTime2.GetYear(),
			(int)awsDateTime2.GetMonth() + 1,
			awsDateTime2.GetDay(),
			awsDateTime2.GetHour(),
			awsDateTime2.GetMinute(),
			awsDateTime2.GetSecond(),
			awsDateTime2.Millis()
		);
		UserPoolId = UserPoolClientType.GetUserPoolId().c_str();
		const Aws::Vector<Aws::String>& CallbackURLsVector = UserPoolClientType.GetCallbackURLs();
		for (int i = 0; i < CallbackURLsVector.size(); i++)
		{
			CallbackURLs.Add(CallbackURLsVector[i].c_str());
		}
	}	
};

USTRUCT(BlueprintType)
struct FUserPoolDescriptionType
{
	GENERATED_BODY()



	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FLambdaConfigType LambdaConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime LastModifiedDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime CreationDate;

	FUserPoolDescriptionType(){}
	FUserPoolDescriptionType(const Aws::CognitoIdentityProvider::Model::UserPoolDescriptionType& UserPoolDescriptionType)
	{
		Name = UserPoolDescriptionType.GetName().c_str();
		LambdaConfig = FLambdaConfigType(UserPoolDescriptionType.GetLambdaConfig());
		const Aws::Utils::DateTime& awsDateTime = UserPoolDescriptionType.GetLastModifiedDate();
		LastModifiedDate = FDateTime(
			awsDateTime.GetYear(),
			(int)awsDateTime.GetMonth() + 1,
			awsDateTime.GetDay(),
			awsDateTime.GetHour(),
			awsDateTime.GetMinute(),
			awsDateTime.GetSecond(),
			awsDateTime.Millis()
		);
		const Aws::Utils::DateTime& awsDateTime2 = UserPoolDescriptionType.GetCreationDate();
		CreationDate = FDateTime(
			awsDateTime2.GetYear(),
			(int)awsDateTime2.GetMonth() + 1,
			awsDateTime2.GetDay(),
			awsDateTime2.GetHour(),
			awsDateTime2.GetMinute(),
			awsDateTime2.GetSecond(),
			awsDateTime2.Millis()
		);
	}
};

USTRUCT(BlueprintType)
struct FUserPoolPolicyType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	int32 PasswordPolicy;
	
	FUserPoolPolicyType(){}
	FUserPoolPolicyType(const Aws::CognitoIdentityProvider::Model::UserPoolPolicyType& UserPoolPolicyType)
	{
		PasswordPolicy = UserPoolPolicyType.GetPasswordPolicy().GetMinimumLength();
	}
};

USTRUCT(BlueprintType)
struct FUserPoolType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString PoolName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FUserPoolPolicyType Policies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FLambdaConfigType LambdaConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime LastModifiedDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime CreationDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FSchemaAttributeType> SchemaAttributes;
	

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString AliasAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString UsernameAttributes;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString SmsVerificationMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString EmailVerificationMessage;

	FUserPoolType(){}
	FUserPoolType(const Aws::CognitoIdentityProvider::Model::UserPoolType& UserPoolType)
	{
		PoolName = UserPoolType.GetName().c_str();
		Policies = FUserPoolPolicyType(UserPoolType.GetPolicies());
		LambdaConfig = FLambdaConfigType(UserPoolType.GetLambdaConfig());
		const Aws::Utils::DateTime& awsDateTime = UserPoolType.GetLastModifiedDate();
		LastModifiedDate = FDateTime(
			awsDateTime.GetYear(),
			(int)awsDateTime.GetMonth() + 1,
			awsDateTime.GetDay(),
			awsDateTime.GetHour(),
			awsDateTime.GetMinute(),
			awsDateTime.GetSecond(),
			awsDateTime.Millis()
		);
		const Aws::Utils::DateTime& awsDateTime2 = UserPoolType.GetCreationDate();
		CreationDate = FDateTime(
			awsDateTime2.GetYear(),
			(int)awsDateTime2.GetMonth() + 1,
			awsDateTime2.GetDay(),
			awsDateTime2.GetHour(),
			awsDateTime2.GetMinute(),
			awsDateTime2.GetSecond(),
			awsDateTime2.Millis()
		);
		const Aws::Vector<Aws::CognitoIdentityProvider::Model::SchemaAttributeType>& SchemaAttributesVector = UserPoolType.GetSchemaAttributes();
		for (int i = 0; i < SchemaAttributesVector.size(); i++)
		{
			SchemaAttributes.Add(FSchemaAttributeType(SchemaAttributesVector[i]));
		}
	}
};



USTRUCT(BlueprintType)
struct FIdentityProviderType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString UserPoolId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ProviderName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EIdentityProviderType> ProviderType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TMap<FString,FString> ProviderDetails;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TMap<FString,FString> AttributeMapping;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FString> IdpIdentifiers;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime LastModifiedDate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime CreationDate;

	FIdentityProviderType()
	{
		
	}
	FIdentityProviderType(const Aws::CognitoIdentityProvider::Model::IdentityProviderType& IdentityProviderType)
	{
		UserPoolId = IdentityProviderType.GetUserPoolId().c_str();
		ProviderName = IdentityProviderType.GetProviderName().c_str();
		ProviderType = static_cast<EIdentityProviderType>(IdentityProviderType.GetProviderType());
		const Aws::Map<Aws::String, Aws::String>& ProviderDetailsMap = IdentityProviderType.GetProviderDetails();
		for (auto& Elem : ProviderDetailsMap)
		{
			ProviderDetails.Add(Elem.first.c_str(), Elem.second.c_str());
		}
		const Aws::Map<Aws::String, Aws::String>& AttributeMappingMap = IdentityProviderType.GetAttributeMapping();
		for (auto& Elem : AttributeMappingMap)
		{
			AttributeMapping.Add(Elem.first.c_str(), Elem.second.c_str());
		}
		const Aws::Vector<Aws::String>& IdpIdentifiersVector = IdentityProviderType.GetIdpIdentifiers();
		for (int i = 0; i < IdpIdentifiersVector.size(); i++)
		{
			IdpIdentifiers.Add(IdpIdentifiersVector[i].c_str());
		}
		const Aws::Utils::DateTime& awsDateTime = IdentityProviderType.GetLastModifiedDate();
		LastModifiedDate = FDateTime(
			awsDateTime.GetYear(),
			(int)awsDateTime.GetMonth() + 1,
			awsDateTime.GetDay(),
			awsDateTime.GetHour(),
			awsDateTime.GetMinute(),
			awsDateTime.GetSecond(),
			awsDateTime.Millis()
		);
		const Aws::Utils::DateTime& awsDateTime2 = IdentityProviderType.GetCreationDate();
		CreationDate = FDateTime(
			awsDateTime2.GetYear(),
			(int)awsDateTime2.GetMonth() + 1,
			awsDateTime2.GetDay(),
			awsDateTime2.GetHour(),
			awsDateTime2.GetMinute(),
			awsDateTime2.GetSecond(),
			awsDateTime2.Millis()
		);
	}
};

USTRUCT(BlueprintType)
struct FUserType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TArray<FAttributeType> Attributes;

	FUserType(){}
	FUserType(const Aws::CognitoIdentityProvider::Model::UserType& UserType)
	{
		Username = UserType.GetUsername().c_str();
		for (auto Attribute : UserType.GetAttributes())
		{
			Attributes.Add(FAttributeType(Attribute));
		}
	}
};

UENUM(BlueprintType)
enum EDefaultEmailOptionType
{
	NOT_SET4 UMETA(DisplayName = "NOT_SET"),
	CONFIRM_WITH_LINK,
	CONFIRM_WITH_CODE
  };

USTRUCT(BlueprintType)
struct FVerificationMessageTemplateType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString SmsMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString EmailMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString EmailSubject;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString EmailMessageByLink;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString EmailSubjectByLink;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EDefaultEmailOptionType> DefaultEmailOption;

	FVerificationMessageTemplateType(){}
	FVerificationMessageTemplateType(const Aws::CognitoIdentityProvider::Model::VerificationMessageTemplateType& VerificationMessageTemplateType)
	{
		SmsMessage = VerificationMessageTemplateType.GetSmsMessage().c_str();
		EmailMessage = VerificationMessageTemplateType.GetEmailMessage().c_str();
		EmailSubject = VerificationMessageTemplateType.GetEmailSubject().c_str();
		EmailMessageByLink = VerificationMessageTemplateType.GetEmailMessageByLink().c_str();
		EmailSubjectByLink = VerificationMessageTemplateType.GetEmailSubjectByLink().c_str();
		DefaultEmailOption = static_cast<EDefaultEmailOptionType>(VerificationMessageTemplateType.GetDefaultEmailOption());
	}
};


USTRUCT(BlueprintType)
struct FCodeDeliveryDetail
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Kit")
	FString AttributeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Kit")
	TEnumAsByte<EDeliveryMediumType> DeliveryMedium;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Identity Kit")
	FString Destination;

	FCodeDeliveryDetail(){}
	FCodeDeliveryDetail(const Aws::CognitoIdentityProvider::Model::CodeDeliveryDetailsType& CodeDeliveryDetailsType)
	{
		AttributeName = CodeDeliveryDetailsType.GetAttributeName().c_str();
		DeliveryMedium = static_cast<EDeliveryMediumType>(CodeDeliveryDetailsType.GetDeliveryMedium());
		Destination = CodeDeliveryDetailsType.GetDestination().c_str();
	}
	
};


USTRUCT(BlueprintType)
struct FRiskConfigurationType
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString UserPoolId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ClientId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FAccountTakeoverRiskConfigurationType AccountTakeoverRiskConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FCompromisedCredentialsRiskConfigurationType CompromisedCredentialsRiskConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FRiskExceptionConfigurationType RiskExceptionConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FDateTime LastModifiedDate;
	FRiskConfigurationType(){}
	FRiskConfigurationType(const Aws::CognitoIdentityProvider::Model::RiskConfigurationType &RiskConfigurationType)
	{
		UserPoolId = RiskConfigurationType.GetUserPoolId().c_str();
		ClientId = RiskConfigurationType.GetClientId().c_str();
		AccountTakeoverRiskConfiguration = FAccountTakeoverRiskConfigurationType(RiskConfigurationType.GetAccountTakeoverRiskConfiguration());
		CompromisedCredentialsRiskConfiguration = FCompromisedCredentialsRiskConfigurationType(RiskConfigurationType.GetCompromisedCredentialsRiskConfiguration());
		RiskExceptionConfiguration = FRiskExceptionConfigurationType(RiskConfigurationType.GetRiskExceptionConfiguration());
		const Aws::Utils::DateTime& awsLastModified = RiskConfigurationType.GetLastModifiedDate();
		LastModifiedDate = FDateTime(
			awsLastModified.GetYear(),
			(int)awsLastModified.GetMonth() + 1,
			awsLastModified.GetDay(),
			awsLastModified.GetHour(),
			awsLastModified.GetMinute(),
			awsLastModified.GetSecond(),
			awsLastModified.Millis()
		);
		
	}

};


