
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminCreateUser_Async.generated.h"


UENUM(BlueprintType)
enum MessageActionType
{
	NOT_SET30 UMETA(DisplayName = "NOT_SET"),
	RESEND,
	SUPPRESS
  };
USTRUCT(BlueprintType)
struct FAdminCreateUserReq
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TMap<FString, FString> ClientMetaData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TArray<TEnumAsByte<EDeliveryMediumType>> DesiredDeliveryMediums;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	bool ForceAliasCreation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TEnumAsByte<MessageActionType> MessageAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString TemporaryPassword;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TArray<FAttributeType> UserAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString Username;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	TArray<FAttributeType> ValidationData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString UserPoolId;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAdminCreateUserAsyncCompleted, FUserType, User, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminCreateUser_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminCreateUser_Async* AdminCreateUser_Async(FAdminCreateUserReq AdminCreateUserReq);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FOnAdminCreateUserAsyncCompleted OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAdminCreateUserAsyncCompleted OnFailure;

	FAdminCreateUserReq Var_AdminCreateUserReq;
	
};
