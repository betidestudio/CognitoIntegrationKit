
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "UpdateResourceServer_Async.generated.h"

USTRUCT(BlueprintType)
struct FUpdateResourceServerReq
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString UserPoolId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Identifier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FResourceServerScopeType> Scopes;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnUpdateResourceServerAsyncCompleted, FResourceServerType,ResourceServer,const FCognitoError&, CognitoError);

UCLASS()
class COGNITOINTEGRATIONKIT_API UUpdateResourceServer_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UUpdateResourceServer_Async* UpdateResourceServer_Async(FUpdateResourceServerReq Request);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FUpdateResourceServerReq Var_UpdateResourceServerRequest;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateResourceServerAsyncCompleted OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnUpdateResourceServerAsyncCompleted OnFailure;

};
