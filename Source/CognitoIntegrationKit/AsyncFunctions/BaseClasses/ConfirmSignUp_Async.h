
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ConfirmSignUp_Async.generated.h"

USTRUCT(BlueprintType)
struct FConfirmSignUpRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ClientId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TMap<FString, FString> ClientMetadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ConfirmationCode;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	bool bForceAliasCreation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString SecretHash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FUserContextDataType UserContextData;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FConfirmSignUpAsyncResponse, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UConfirmSignUp_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UConfirmSignUp_Async* ConfirmSignUp_Async(FConfirmSignUpRequest Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FConfirmSignUpRequest Var_Request;

	UPROPERTY(BlueprintAssignable)
	FConfirmSignUpAsyncResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FConfirmSignUpAsyncResponse OnFailure;

};
