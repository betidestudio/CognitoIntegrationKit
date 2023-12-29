//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/Public/CIK_Object.h"
#include "MainClasses/CIKAsyncFunction.h"
#include "CIK_LoginWithEmail.generated.h"

USTRUCT(BlueprintType)
struct FLoginWithEmailSuccessResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString AccessToken;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString IdToken;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString RefreshToken;

	//Time is in seconds
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 TokenExpiresIn;
};

USTRUCT(BlueprintType)
struct FLoginWithEmailFailureResponse
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

