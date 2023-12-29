
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "GetUser_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_SixParams(FGetUserDelegate, TArray<FMFAOptionType>, MFAOptions, FString, PreferredMfaSetting, TArray<FAttributeType>, UserAttributes, TArray<FString>, UserMFASettingList, FString, Username, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UGetUser_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UGetUser_Async* GetUser_Async(FString AccessToken);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;

	UPROPERTY(BlueprintAssignable)
	FGetUserDelegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGetUserDelegate OnFailure;

};
