
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminUpdateUserAttributes_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdminUpdateUserAttributesAsync, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminUpdateUserAttributes_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminUpdateUserAttributes_Async* AdminUpdateUserAttributes_Async();

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	TMap<FString, FString> Var_ClientMetadata;
	TArray<FAttributeType> Var_AttributesToUpdate;
	FString Var_Username;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FOnAdminUpdateUserAttributesAsync OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAdminUpdateUserAttributesAsync OnFailure;

};
