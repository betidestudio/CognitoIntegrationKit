//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CIK_Object.h"
#include "CognitoDataTypes.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CIKAsyncFunction.generated.h"
/**
 * 
 */
UCLASS()
class COGNITOINTEGRATIONKIT_API UCIKAsyncFunction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:
	virtual void Activate() override;

	virtual void ContinueProcess(UCIK_Object* CognitoObject);

	virtual void ExecuteFailure(FCognitoError Error);


	static FDateTime ConvertAwsDateTimeToFDateTime(const Aws::Utils::DateTime& awsDateTime)
	{
		// Extract the components from Aws::Utils::DateTime
		int year = awsDateTime.GetYear();
		int basicMonth = (int)awsDateTime.GetMonth() + 1;
		int day = awsDateTime.GetDay();
		int hour = awsDateTime.GetHour();
		int minute = awsDateTime.GetMinute();
		int second = awsDateTime.GetSecond();
		// Depending on the precision you need, you might also want to get milliseconds
		int millisecond = awsDateTime.Millis();

		// Create an FDateTime instance with these components
		FDateTime unrealDateTime(year, basicMonth, day, hour, minute, second, millisecond);

		return unrealDateTime;
	}
};
