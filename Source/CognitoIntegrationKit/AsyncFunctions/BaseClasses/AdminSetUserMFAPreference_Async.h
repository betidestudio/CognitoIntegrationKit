
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "AdminSetUserMFAPreference_Async.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAdminSetUserMFAPreferenceAsyncOutputPin, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API UAdminSetUserMFAPreference_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static UAdminSetUserMFAPreference_Async* AdminSetUserMFAPreference_Async(FSMSMfaSettingsType MfaSettings, FSoftwareTokenMfaSettingsType SoftwareTokenMfaSettings, FString Username, FString UserPoolId);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FSMSMfaSettingsType Var_MfaSettings;
	FSoftwareTokenMfaSettingsType Var_SoftwareTokenMfaSettings;
	FString Var_Username;
	FString Var_UserPoolId;

	UPROPERTY(BlueprintAssignable)
	FAdminSetUserMFAPreferenceAsyncOutputPin OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FAdminSetUserMFAPreferenceAsyncOutputPin OnFailure;
};
