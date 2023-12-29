
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "SignUp_Async.generated.h"

USTRUCT(BlueprintType)
struct FSignUpRequest
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FAnalyticsMetadataType AnalyticsMetadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString ClientId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TMap<FString, FString> ClientMetadata;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString Password;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString SecretHash;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TArray<FAttributeType> UserAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FUserContextDataType UserContextData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TArray<FAttributeType> ValidationData;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FSignUpAsyncOutputPin, FCodeDeliveryDetailsType, CodeDeliveryDetails, bool,bUserConfirmed, FString, Username, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API USignUp_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static USignUp_Async* SignUp_Async(FSignUpRequest SignUpRequest);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FSignUpRequest Var_SignUpRequest;

	UPROPERTY(BlueprintAssignable)
	FSignUpAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FSignUpAsyncOutputPin OnFailure;
};
