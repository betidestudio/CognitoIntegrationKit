
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminSetUserSettings_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAdminSetUserSettingsAsyncOutputPin, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminSetUserSettings_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminSetUserSettings_Async* AdminSetUserSettings_Async(TArray<FMFAOptionType> MFAOptions, FString UserPoolId, FString Username);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	TArray<FMFAOptionType> Var_MFAOptions;
	FString Var_UserPoolId;
	FString Var_Username;

	UPROPERTY(BlueprintAssignable)
	FOnAdminSetUserSettingsAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnAdminSetUserSettingsAsyncOutputPin OnFailure;
};
