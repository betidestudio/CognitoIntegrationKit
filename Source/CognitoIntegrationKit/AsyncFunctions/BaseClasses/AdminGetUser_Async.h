
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminGetUser_Async.generated.h"


UENUM(BlueprintType)
enum EUserStatusType
{
	NOT_SET24 UMETA(DisplayName = "NOT_SET"),
	UNCONFIRMED,
	CONFIRMED,
	ARCHIVED,
	COMPROMISED,
	UNKNOWN1 UMETA(DisplayName = "UNKNOWN"),
	RESET_REQUIRED,
	FORCE_CHANGE_PASSWORD
  };

USTRUCT(BlueprintType)
struct FAdminGetUserResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	bool bEnabled = false;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	TArray<FMFAOptionType> MFAOptions;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	FString PreferredMfaSetting;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	TArray<FAttributeType> UserAttributes;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	FDateTime UserCreateDate;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	FDateTime UserLastModifiedDate;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	TArray<FString> UserMFASettingList;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	FString Username;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	TEnumAsByte<EUserStatusType> UserStatus;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAdminGetUserAsyncOutputPin, const FAdminGetUserResponse&, Response, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminGetUser_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminGetUser_Async* AdminGetUser_Async(FString UserPoolId, FString Username);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_UserPoolId;
	FString Var_Username;

	UPROPERTY(BlueprintAssignable)
	FAdminGetUserAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminGetUserAsyncOutputPin OnFailure;
	
};
