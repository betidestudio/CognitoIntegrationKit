
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CIK_Object.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "VerifyUserAttribute_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FVerifyUserAttribute_Delegate, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UVerifyUserAttribute_Async : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Cogntio Identity Kit")
	static UVerifyUserAttribute_Async* VerifyUserAttribute_Async(UObject* WorldContextObject, FString AttributeName, FString AccessToken, FString Code);

	void Activate() override;

	void ContinueProcess(UCIK_Object* CognitoObject);

	UPROPERTY(BlueprintAssignable)
	FVerifyUserAttribute_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FVerifyUserAttribute_Delegate OnFailure;

	FString Var_AttributeName;
	FString Var_AccessToken;
	FString Var_Code;

};
