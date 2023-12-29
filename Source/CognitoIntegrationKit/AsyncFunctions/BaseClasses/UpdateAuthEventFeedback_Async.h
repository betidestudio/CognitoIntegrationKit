
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "UpdateAuthEventFeedback_Async.generated.h"

UENUM(BlueprintType)
enum FFeedbackValueType
{
	NOT_SET8 UMETA(DisplayName = "NOT_SET"),
	Valid1 UMETA(DisplayName = "Valid"),
	Invalid1 UMETA(DisplayName = "Invalid")
};

USTRUCT(BlueprintType)
struct FUpdateAuthEventFeedbackReq
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Kit")
	FString EventId = "";

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Kit")
	FString FeedbackToken = "";

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Kit")
	TEnumAsByte<FFeedbackValueType> FeedbackValue = FFeedbackValueType::NOT_SET8;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Kit")
	FString Username = "";

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Kit")
	FString UserPoolId = "";
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateAuthEventFeedbackResult, const FCognitoError&, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UUpdateAuthEventFeedback_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UUpdateAuthEventFeedback_Async* UpdateAuthEventFeedback_Async(const FUpdateAuthEventFeedbackReq& UpdateAuthEventFeedbackReq);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FUpdateAuthEventFeedbackResult OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FUpdateAuthEventFeedbackResult OnFailure;

	FUpdateAuthEventFeedbackReq Var_UpdateAuthEventFeedbackReq;
};
