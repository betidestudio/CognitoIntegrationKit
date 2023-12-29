//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/Public/CIK_Object.h"
#include "CIK_SignUpWithEmail.generated.h"

USTRUCT(BlueprintType)
struct FSignUpWithEmailSuccessResponse
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString RequestID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	bool bUserConfirmed;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString UUID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString JsonForCodeDeliveryDetails;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	int32 RetryCount;
};

USTRUCT(BlueprintType)
struct FSignUpWithEmailFailureResponse
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString ErrorMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	bool bCanUserRetry;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString GetMessageA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString GetMessageW;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
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

