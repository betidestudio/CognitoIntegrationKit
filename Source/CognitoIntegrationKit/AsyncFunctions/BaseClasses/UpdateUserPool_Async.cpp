
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "UpdateUserPool_Async.h"

#include "aws/cognito-idp/model/UpdateUserPoolRequest.h"

UUpdateUserPool_Async* UUpdateUserPool_Async::UpdateUserPool_Async(UObject* WorldContextObject, struct FUpdateUserPoolRequest1 UpdateUserPoolRequest)
{
	UUpdateUserPool_Async* Node = NewObject<UUpdateUserPool_Async>();
	Node->Var_UpdateUserPoolRequest = UpdateUserPoolRequest;
	return Node;
}

void UUpdateUserPool_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
	Aws::CognitoIdentityProvider::Model::UpdateUserPoolRequest UpdateUserPoolRequest;
	UpdateUserPoolRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.UserPoolId));
	UpdateUserPoolRequest.SetAdminCreateUserConfig(Aws::CognitoIdentityProvider::Model::AdminCreateUserConfigType().WithAllowAdminCreateUserOnly(Var_UpdateUserPoolRequest.AdminCreateUserConfig.AllowAdminCreateUserOnly).WithInviteMessageTemplate(Aws::CognitoIdentityProvider::Model::MessageTemplateType().WithEmailMessage(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.AdminCreateUserConfig.InviteMessageTemplate.EmailMessage)).WithEmailSubject(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.AdminCreateUserConfig.InviteMessageTemplate.EmailSubject)).WithSMSMessage(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.AdminCreateUserConfig.InviteMessageTemplate.SMSMessage))).WithUnusedAccountValidityDays(Var_UpdateUserPoolRequest.AdminCreateUserConfig.UnusedAccountValidityDays));
	Aws::CognitoIdentityProvider::Model::EmailConfigurationType emailConfig;
	Aws::CognitoIdentityProvider::Model::EmailSendingAccountType emailSendingAccountType;
	emailSendingAccountType = Aws::CognitoIdentityProvider::Model::EmailSendingAccountTypeMapper::GetEmailSendingAccountTypeForName(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.EmailConfiguration.EmailSendingAccount));
	emailConfig.SetConfigurationSet(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.EmailConfiguration.ConfigurationSet));
	emailConfig.SetEmailSendingAccount(emailSendingAccountType);
	emailConfig.SetFrom(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.EmailConfiguration.From));
	emailConfig.SetReplyToEmailAddress(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.EmailConfiguration.ReplyToEmailAddress));
	emailConfig.SetSourceArn(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.EmailConfiguration.SourceArn));
	UpdateUserPoolRequest.SetEmailConfiguration(emailConfig);

	
	
	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolRequest&, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if (outcome.IsSuccess())
			{
				OnSuccess.Broadcast(FCognitoError());
			}
			else
			{
				FCognitoError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
				Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
				OnFailure.Broadcast(Error);
			}
			SetReadyToDestroy();
		});
	};
	CognitoObject->Var_CognitoIPClient->UpdateUserPoolAsync(UpdateUserPoolRequest, AsyncCallback);
}

void UUpdateUserPool_Async::ExecuteFailure(FCognitoError Error)
{
	OnFailure.Broadcast(Error);
}


