
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "SetUserSettings_Async.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnSetUserSettingsAsync, FCognitoError, Error);
UCLASS()
class COGNITOINTEGRATIONKIT_API USetUserSettings_Async : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static USetUserSettings_Async* SetUserSettings_Async(FString AccessToken, TArray<FMFAOptionType> MFAOptions);

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

	FString Var_AccessToken;
	TArray<FMFAOptionType> Var_MFAOptions;

	UPROPERTY(BlueprintAssignable)
	FOnSetUserSettingsAsync OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FOnSetUserSettingsAsync OnFailure;

};
