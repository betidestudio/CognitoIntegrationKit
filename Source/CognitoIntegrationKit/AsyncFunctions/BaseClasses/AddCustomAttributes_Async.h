
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AddCustomAttributes_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAddCustomAttributesResponse, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAddCustomAttributes_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit", DisplayName = "Add Custom Attributes")
	static UAddCustomAttributes_Async* AddCustomAttributes_Async(TArray<FSchemaAttributeType> Attributes, const FString& UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	TArray<FSchemaAttributeType> Var_Attributes;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FAddCustomAttributesResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAddCustomAttributesResponse OnFailure;
};
