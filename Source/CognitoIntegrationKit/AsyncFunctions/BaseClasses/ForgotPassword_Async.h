
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ForgotPassword_Async.generated.h"

USTRUCT(BlueprintType)
struct FForgotPassword_Req
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString ClientID;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FAnalyticsMetadataType AnalyticsMetadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	TMap<FString,FString> ClientMetadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FString SecretHash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito")
	FUserContextDataType UserContextData;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FForgotPassword_Delegate, FCodeDeliveryDetailsType,CodeDeliveryDetails, FCognitoError, Error);


UCLASS()
class COGNITOINTEGRATIONKIT_API UForgotPassword_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UForgotPassword_Async* ForgotPassword_Async(FForgotPassword_Req Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FForgotPassword_Req Var_ForgotPassword_Req;

	UPROPERTY(BlueprintAssignable)
	FForgotPassword_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FForgotPassword_Delegate OnFailure;

};
