
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminLinkProviderForUser_Async.generated.h"

USTRUCT(BlueprintType)
struct FAdminLinkProviderRequest
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FProviderUserIdentifierType DestinationUser;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FProviderUserIdentifierType SourceUser;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString UserPoolId;
	
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdminLinkProviderForUserResponse, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminLinkProviderForUser_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminLinkProviderForUser_Async* AdminLinkProviderForUser_Async(FAdminLinkProviderRequest AdminLinkProviderRequest);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	UPROPERTY(BlueprintAssignable)
	FAdminLinkProviderForUserResponse OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminLinkProviderForUserResponse OnFailure;
	
	FAdminLinkProviderRequest Var_AdminLinkProviderRequest;
};
