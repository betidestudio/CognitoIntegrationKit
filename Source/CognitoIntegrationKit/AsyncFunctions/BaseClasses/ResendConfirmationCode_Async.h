
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ResendConfirmationCode_Async.generated.h"

USTRUCT(BlueprintType)
struct FResentConfirmationCodeRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FAnalyticsMetadataType AnalyticsMetadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString ClientId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TMap<FString, FString> ClientMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString SecretHash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FUserContextDataType UserContextData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString Username;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FResendConfirmationCodeDelegateAsync, const FCodeDeliveryDetailsType&, CodeDeliveryDetails, const FCognitoError&, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UResendConfirmationCode_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UResendConfirmationCode_Async* ResendConfirmationCode_Async(FResentConfirmationCodeRequest Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FResentConfirmationCodeRequest Var_ResendConfirmationCodeRequest;

	UPROPERTY(BlueprintAssignable)
	FResendConfirmationCodeDelegateAsync OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FResendConfirmationCodeDelegateAsync OnFailure;

};
