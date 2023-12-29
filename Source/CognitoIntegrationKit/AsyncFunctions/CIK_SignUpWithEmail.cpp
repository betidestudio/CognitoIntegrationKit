//Copyright (c) 2023 Betide Studio. All Rights Reserved.


#include "CIK_SignUpWithEmail.h"
#include "Runtime/CoreUObject/Public/UObject/UObjectIterator.h"
#include "CIK_Object.h"
#include "aws/cognito-idp/model/SignUpRequest.h"


UCIK_SignUpWithEmail* UCIK_SignUpWithEmail::SignUpWithEmail(UObject* WorldContextObject, const FString& Username,
                                                            const FString& Email, const FString& Password)
{
	UCIK_SignUpWithEmail* SignUpWithEmail = NewObject<UCIK_SignUpWithEmail>();
	SignUpWithEmail->Var_Username = Username;
	SignUpWithEmail->Var_Email = Email;
	SignUpWithEmail->Var_Password = Password;
	SignUpWithEmail->Var_WorldContextObject = WorldContextObject;
	return SignUpWithEmail;
}

void UCIK_SignUpWithEmail::Activate()
{
	FSignUpWithEmailFailureResponse Local_FailureResponse;
	Super::Activate();
	TArray<UCIK_Object*> Objects;
	for (TObjectIterator<UCIK_Object> Itr; Itr; ++Itr)
	{
		Objects.Add(*Itr);
	}
	if(Objects[0])
	{
		if(Objects[0]->CognitoClientID.IsEmpty())
		{
			OnFailure.Broadcast(FSignUpWithEmailSuccessResponse(), Local_FailureResponse);
			SetReadyToDestroy();
		}
		else
		{
			ContinueSignUp(Objects[0]);
		}
	}
	else
	{
		Local_FailureResponse.ErrorMessage = "No object found";
		OnFailure.Broadcast(FSignUpWithEmailSuccessResponse(),Local_FailureResponse);
		SetReadyToDestroy();
	}

}

void UCIK_SignUpWithEmail::ContinueSignUp(UCIK_Object* CognitoObject)
{
	Aws::CognitoIdentityProvider::Model::SignUpRequest SignUpRequest;
	SignUpRequest.AddUserAttributes(Aws::CognitoIdentityProvider::Model::AttributeType().WithName("email").WithValue(TCHAR_TO_UTF8(*Var_Email)));
	SignUpRequest.SetUsername(TCHAR_TO_UTF8(*Var_Username));
	SignUpRequest.SetPassword(TCHAR_TO_UTF8(*Var_Password));
	SignUpRequest.SetClientId(TCHAR_TO_UTF8(*CognitoObject->CognitoClientID));
	
	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::SignUpRequest&, const Aws::CognitoIdentityProvider::Model::SignUpOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if(outcome.IsSuccess())
			{
				FSignUpWithEmailSuccessResponse SuccessResponse;
				SuccessResponse.RequestID = outcome.GetResult().GetUserSub().c_str();
				SuccessResponse.bUserConfirmed = outcome.GetResult().GetUserConfirmed();
				SuccessResponse.UUID = outcome.GetResult().GetUserSub().c_str();
				Aws::String JsonForCodeDeliveryDetails ;
				outcome.GetResult().GetCodeDeliveryDetails().Jsonize().AsString(JsonForCodeDeliveryDetails);
				SuccessResponse.JsonForCodeDeliveryDetails = JsonForCodeDeliveryDetails.c_str();
				OnSuccess.Broadcast(SuccessResponse, FSignUpWithEmailFailureResponse());
			}
			else
			{
				FSignUpWithEmailFailureResponse FailureResponse;
				FailureResponse.ErrorMessage = outcome.GetError().GetMessage().c_str();
				FailureResponse.bCanUserRetry = outcome.GetError().ShouldRetry();
				FailureResponse.ExceptionName = outcome.GetError().GetExceptionName().c_str();
				FailureResponse.GetMessageW = outcome.GetError().GetMessage().c_str();
				FailureResponse.GetMessageA = outcome.GetError().GetMessage().c_str();
				OnFailure.Broadcast(FSignUpWithEmailSuccessResponse(), FailureResponse);
			}
			SetReadyToDestroy();
		});
	};
	CognitoObject->Var_CognitoIPClient->SignUpAsync(SignUpRequest, AsyncCallback);
}
