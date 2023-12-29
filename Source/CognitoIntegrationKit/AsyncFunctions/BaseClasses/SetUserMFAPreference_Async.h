
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "SetUserMFAPreference_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetUserMFAPreference, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API USetUserMFAPreference_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static USetUserMFAPreference_Async* SetUserMFAPreference_Async(FString AccessToken, FSMSMfaSettingsType SMSMfaSettings, FSoftwareTokenMfaSettingsType SoftwareTokenMfaSettings);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;
	FSMSMfaSettingsType Var_SMSMfaSettings;
	FSoftwareTokenMfaSettingsType Var_SoftwareTokenMfaSettings;

	UPROPERTY(BlueprintAssignable)
	FOnSetUserMFAPreference OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSetUserMFAPreference OnFailure;

};
