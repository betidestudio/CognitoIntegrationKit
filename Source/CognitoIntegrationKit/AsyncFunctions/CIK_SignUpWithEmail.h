﻿//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/Public/CIK_Object.h"
#include "CIK_SignUpWithEmail.generated.h"

USTRUCT(BlueprintType)
struct FSignUpWithEmailSuccessResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString RequestID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bUserConfirmed;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UUID;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString JsonForCodeDeliveryDetails;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 RetryCount;
};

USTRUCT(BlueprintType)
struct FSignUpWithEmailFailureResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ErrorMessage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bCanUserRetry;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GetMessageA;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GetMessageW;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ExceptionName;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCognitoIdentityKitSignUpWithEmail, const FSignUpWithEmailSuccessResponse&, SuccessResponse, const FSignUpWithEmailFailureResponse&, FailureResponse);




UCLASS()
class COGNITOINTEGRATIONKIT_API UCIK_SignUpWithEmail : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Cognito Identity Kit")
	static UCIK_SignUpWithEmail* SignUpWithEmail(UObject* WorldContextObject, const FString& Username,const FString& Email, const FString& Password);

	void Activate() override;

	void ContinueSignUp(UCIK_Object* CognitoObject);

	UPROPERTY(BlueprintAssignable)
	FOnCognitoIdentityKitSignUpWithEmail OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnCognitoIdentityKitSignUpWithEmail OnFailure;

private:
	FString Var_Username;
	FString Var_Email;
	FString Var_Password;
	UObject* Var_WorldContextObject;
};

