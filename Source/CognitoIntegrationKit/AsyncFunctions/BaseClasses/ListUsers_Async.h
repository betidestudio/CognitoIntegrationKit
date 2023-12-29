
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "ListUsers_Async.generated.h"

USTRUCT(BlueprintType)
struct FListUsersRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString UserPoolId = "";
	
	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString Filter = "";

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	int32 Limit = 0;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	FString PaginationToken = "";

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Integration Kit")
	TArray<FString> AttributesToGet = {};
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FListUsersAsyncOutputPin, FString, PaginationToken, TArray<FUserType>, Users, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UListUsers_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UListUsers_Async* ListUsers_Async(FListUsersRequest Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FListUsersRequest Var_Request;

	UPROPERTY(BlueprintAssignable)
	FListUsersAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FListUsersAsyncOutputPin OnFailure;

	

};
