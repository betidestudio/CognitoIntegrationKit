
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "UpdateGroup_Async.generated.h"

USTRUCT(BlueprintType)
struct FUpdateGroupReq
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString GroupName;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString UserPoolId;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString Description;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Provider")
	FString RoleArn;

	UPROPERTY(BlueprintReadWrite, Category = "Cognito Identity Provider")
	int32 Precedence;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FUpdateGroupAsyncOutputPin, FGroupType, Group, FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UUpdateGroup_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UUpdateGroup_Async* UpdateGroup_Async(FUpdateGroupReq Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FUpdateGroupAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FUpdateGroupAsyncOutputPin OnFailure;

	FUpdateGroupReq Var_UpdateGroupReq;


};
