
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminUpdateAuthEventFeedback_Async.generated.h"

/**
 * 
 */

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdminUpdateAuthEventFeedbackAsyncOutputPin, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminUpdateAuthEventFeedback_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminUpdateAuthEventFeedback_Async* AdminUpdateAuthEventFeedback_Async(FString EventID, TEnumAsByte<EFeedbackValueType> FeedbackValue, FString UserPoolId, FString Username);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_EventID;
	TEnumAsByte<EFeedbackValueType> Var_FeedbackValue;
	FString Var_UserPoolId;
	FString Var_Username;

	UPROPERTY(BlueprintAssignable)
	FOnAdminUpdateAuthEventFeedbackAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAdminUpdateAuthEventFeedbackAsyncOutputPin OnFailure;
};
