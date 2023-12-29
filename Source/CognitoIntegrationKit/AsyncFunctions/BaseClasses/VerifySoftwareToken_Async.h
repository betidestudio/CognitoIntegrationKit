
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CIK_Object.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "VerifySoftwareToken_Async.generated.h"

UENUM(BlueprintType)
enum EResponStatus
{
	NOT_SET41 UMETA(DisplayName = "NOT_SET"),
	Success2 UMETA(DisplayName = "Success"),
	Error_
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FVerifySoftwareToken_Delegate, FString, Session, TEnumAsByte<EResponStatus>, Status,FCognitoError, Error);

UCLASS()
class COGNITOINTEGRATIONKIT_API UVerifySoftwareToken_Async : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "Cogntio Identity Kit")
	static UVerifySoftwareToken_Async* VerifySoftwareToken_Async(UObject* WorldContextObject, const FString& AccessToken, const FString& FriendlyDeviceName, const FString& Session, const FString& UserCode);

	void Activate() override;

	UPROPERTY(BlueprintAssignable)
	FVerifySoftwareToken_Delegate OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FVerifySoftwareToken_Delegate OnFailure;

	void ContinueProcess(UCIK_Object* CognitoObject);

	FString Var_Session;
	FString Var_UserCode;
	FString Var_FriendlyDeviceName;
	FString Var_AccessToken;
};
