
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "SetUserPoolMfaConfig_Async.generated.h"

UENUM(BlueprintType)
enum EUserPoolMfaType
{
	NOT_SET23 UMETA(DisplayName = "NOT_SET"),
	OFF,
	ON,
	OPTIONAL
  };
USTRUCT(BlueprintType)
struct FSetUserPoolMfaConfigReq
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TEnumAsByte<EUserPoolMfaType> MfaConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FSmsMfaConfigType SmsMfaConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FSoftwareTokenMfaConfigType SoftwareTokenMfaConfiguration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString UserPoolId;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSetUserPoolMfaConfigResult, TEnumAsByte<EUserPoolMfaType>, MfaConfiguration, FSmsMfaConfigType, SmsMfaConfiguration, FSoftwareTokenMfaConfigType, SoftwareTokenMfaConfiguration, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API USetUserPoolMfaConfig_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static USetUserPoolMfaConfig_Async* SetUserPoolMfaConfig_Async(FSetUserPoolMfaConfigReq Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FSetUserPoolMfaConfigReq Var_Request;

	UPROPERTY(BlueprintAssignable)
	FSetUserPoolMfaConfigResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FSetUserPoolMfaConfigResult OnFailure;
};
