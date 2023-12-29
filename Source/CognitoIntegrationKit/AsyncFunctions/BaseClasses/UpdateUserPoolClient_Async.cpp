
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "UpdateUserPoolClient_Async.h"

#include "aws/cognito-idp/model/UpdateUserPoolClientRequest.h"

UUpdateUserPoolClient_Async* UUpdateUserPoolClient_Async::UpdateUserPoolClient_Async(UObject* WorldContextObject, struct FUpdateUserPoolRequest UpdateUserPoolRequest)
{
	UUpdateUserPoolClient_Async* Node = NewObject<UUpdateUserPoolClient_Async>();
	Node->Var_UpdateUserPoolRequest = UpdateUserPoolRequest;
	return Node;
}

void UUpdateUserPoolClient_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
	Aws::CognitoIdentityProvider::Model::UpdateUserPoolClientRequest UpdateUserPoolClientRequest;
	UpdateUserPoolClientRequest.SetClientId(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.ClientId));
	UpdateUserPoolClientRequest.SetAccessTokenValidity(Var_UpdateUserPoolRequest.AccessTokenValidity);
	Aws::Vector<Aws::CognitoIdentityProvider::Model::OAuthFlowType> AllowedOAuthFlows;
	for (auto& AllowedOAuthFlow : Var_UpdateUserPoolRequest.AllowedOAuthFlows)
	{
		AllowedOAuthFlows.push_back(Aws::CognitoIdentityProvider::Model::OAuthFlowTypeMapper::GetOAuthFlowTypeForName(TCHAR_TO_UTF8(*AllowedOAuthFlow)));
	}
	UpdateUserPoolClientRequest.SetAllowedOAuthFlows(AllowedOAuthFlows);
	UpdateUserPoolClientRequest.SetAllowedOAuthFlowsUserPoolClient(Var_UpdateUserPoolRequest.AllowedOAuthFlowsUserPoolClient);
	Aws::Vector<Aws::String> AllowedOAuthScopes;
	for (auto& AllowedOAuthScope : Var_UpdateUserPoolRequest.AllowedOAuthScopes)
	{
		AllowedOAuthScopes.push_back(TCHAR_TO_UTF8(*AllowedOAuthScope));
	}
	UpdateUserPoolClientRequest.SetAllowedOAuthScopes(AllowedOAuthScopes);
	Aws::Vector<Aws::String> CallbackURLs;
	for (auto& CallbackURL : Var_UpdateUserPoolRequest.CallbackURLs)
	{
		CallbackURLs.push_back(TCHAR_TO_UTF8(*CallbackURL));
	}
	UpdateUserPoolClientRequest.SetCallbackURLs(CallbackURLs);
	UpdateUserPoolClientRequest.SetClientName(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.ClientName));
	UpdateUserPoolClientRequest.SetDefaultRedirectURI(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.DefaultRedirectURI));
	for (auto& ExplicitAuthFlows : Var_UpdateUserPoolRequest.ExplicitAuthFlows)
	{
		UpdateUserPoolClientRequest.AddExplicitAuthFlows(Aws::CognitoIdentityProvider::Model::ExplicitAuthFlowsTypeMapper::GetExplicitAuthFlowsTypeForName(TCHAR_TO_UTF8(*ExplicitAuthFlows)));
	}
	Aws::Vector<Aws::String> LogoutURLs;
	for (auto& LogoutURL : Var_UpdateUserPoolRequest.LogoutURLs)
	{
		LogoutURLs.push_back(TCHAR_TO_UTF8(*LogoutURL));
	}
	UpdateUserPoolClientRequest.SetLogoutURLs(LogoutURLs);
	UpdateUserPoolClientRequest.SetPreventUserExistenceErrors(Aws::CognitoIdentityProvider::Model::PreventUserExistenceErrorTypesMapper::GetPreventUserExistenceErrorTypesForName(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.PreventUserExistenceErrors)));
	Aws::Vector<Aws::String> ReadAttributes;
	for (auto& ReadAttribute : Var_UpdateUserPoolRequest.ReadAttributes)
	{
		ReadAttributes.push_back(TCHAR_TO_UTF8(*ReadAttribute));
	}
	UpdateUserPoolClientRequest.SetReadAttributes(ReadAttributes);
	UpdateUserPoolClientRequest.SetRefreshTokenValidity(Var_UpdateUserPoolRequest.RefreshTokenValidity);
	Aws::Vector<Aws::String> SupportedIdentityProviders;
	for (auto& SupportedIdentityProvider : Var_UpdateUserPoolRequest.SupportedIdentityProviders)
	{
		SupportedIdentityProviders.push_back(TCHAR_TO_UTF8(*SupportedIdentityProvider));
	}
	UpdateUserPoolClientRequest.SetSupportedIdentityProviders(SupportedIdentityProviders);
	UpdateUserPoolClientRequest.SetUserPoolId(TCHAR_TO_UTF8(*Var_UpdateUserPoolRequest.UserPoolId));
	Aws::Vector<Aws::String> WriteAttributes;
	for (auto& WriteAttribute : Var_UpdateUserPoolRequest.WriteAttributes)
	{
		WriteAttributes.push_back(TCHAR_TO_UTF8(*WriteAttribute));
	}
	UpdateUserPoolClientRequest.SetWriteAttributes(WriteAttributes);
	
	auto AsyncCallback = [this](const Aws::CognitoIdentityProvider::CognitoIdentityProviderClient*, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolClientRequest&, const Aws::CognitoIdentityProvider::Model::UpdateUserPoolClientOutcome& outcome, const std::shared_ptr<const Aws::Client::AsyncCallerContext>)
	{
		AsyncTask(ENamedThreads::GameThread, [outcome, this]()
		{
			if (outcome.IsSuccess())
			{
				OnSuccess.Broadcast(outcome.GetResult().GetRequestId().c_str(), FCognitoError());
			}
			else
			{
				FCognitoError Error;
				Error.ErrorMessage = FString(outcome.GetError().GetMessage().c_str());
				Error.ExceptionName = FString(outcome.GetError().GetExceptionName().c_str());
				Error.GetMessageA = FString(outcome.GetError().GetMessage().c_str());
				Error.GetMessageW = FString(outcome.GetError().GetMessage().c_str());
				Error.ErrorType = static_cast<ECognitoErrors>(outcome.GetError().GetErrorType());
				OnFailure.Broadcast("",Error);
			}
		});
	};

	CognitoObject->Var_CognitoIPClient->UpdateUserPoolClientAsync(UpdateUserPoolClientRequest, AsyncCallback);
	
	
	
}

void UUpdateUserPoolClient_Async::ExecuteFailure(FCognitoError Error)
{
	OnFailure.Broadcast("", Error);
}
