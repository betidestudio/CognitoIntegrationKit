
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "GetCSVHeader_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FGetCSVHeaderDelegate, TArray<FString>, CSVHeader, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UGetCSVHeader_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UGetCSVHeader_Async* GetCSVHeader_Async(FString UserPoolID);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_UserPoolID;
	

	UPROPERTY(BlueprintAssignable)
	FGetCSVHeaderDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetCSVHeaderDelegate OnFailure;
};
