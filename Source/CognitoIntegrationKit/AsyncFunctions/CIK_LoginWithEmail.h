//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
#include "CognitoIntegrationKit/Public/CIK_Object.h"
#include "MainClasses/CIKAsyncFunction.h"
#include "CIK_LoginWithEmail.generated.h"

USTRUCT(BlueprintType)
struct FLoginWithEmailSuccessResponse
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString AccessToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString IdToken;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString RefreshToken;

	//Time is in seconds
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	int32 TokenExpiresIn = 0;
};

USTRUCT(BlueprintType)
struct FLoginWithEmailFailureResponse
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString ErrorMessage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	bool bCanUserRetry = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString GetMessageA;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString GetMessageW;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString ExceptionName;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCognitoIdentityKitLoginWithEmail, const FLoginWithEmailSuccessResponse&, SuccessResponse, const FLoginWithEmailFailureResponse&, FailureResponse);




UCLASS()
class COGNITOINTEGRATIONKIT_API UCIK_LoginWithEmail : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Cognito Identity Kit")
	static UCIK_LoginWithEmail* LoginWithEmail(UObject* WorldContextObject, const FString& Username,const FString& Email, const FString& Password);

	void Activate() override;

	void ContinueSignUp(UCIK_Object* CognitoObject);

	UPROPERTY(BlueprintAssignable)
	FOnCognitoIdentityKitLoginWithEmail OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnCognitoIdentityKitLoginWithEmail OnFailure;

private:
	FString Var_Username;
	FString Var_Password;
	UObject* Var_WorldContextObject;
};

