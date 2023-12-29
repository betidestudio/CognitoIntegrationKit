
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ConfirmForgotPassword_Async.generated.h"

USTRUCT(BlueprintType)
struct FConfirmForgotPasswordReq
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	FString ClientId;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	TMap<FString, FString> ClientMetadata;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	FString ConfirmationCode;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	FString Password;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	FString SecretHash;
	
	UPROPERTY(BlueprintReadWrite, Category = "Cognito")
	FString Username;
	
};
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConfirmForgotPasswordDelegate, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UConfirmForgotPassword_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UConfirmForgotPassword_Async* ConfirmForgotPassword_Async(FConfirmForgotPasswordReq Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FConfirmForgotPasswordDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FConfirmForgotPasswordDelegate OnFailure;
	

	
	FConfirmForgotPasswordReq Var_ConfirmForgotPasswordReq;
};
