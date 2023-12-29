
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "CreateUserPool_Async.h"

#include "aws/cognito-idp/model/CreateUserPoolRequest.h"

UCreateUserPool_Async* UCreateUserPool_Async::CreateUserPool_Async(FCreateUserPoolRequest CreateUserPoolRequest)
{
    UCreateUserPool_Async* Node = NewObject<UCreateUserPool_Async>();
    Node->Var_Request = CreateUserPoolRequest;
    return Node;
}

void UCreateUserPool_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
    Aws::CognitoIdentityProvider::Model::CreateUserPoolRequest CreateUserPoolRequest;
    CreateUserPoolRequest.SetPoolName(TCHAR_TO_UTF8(*Var_Request.PoolName));
    CreateUserPoolRequest.SetAccountRecoverySetting(Var_Request.AccountRecoverySetting.ToAccountRecoverySettingType());
    CreateUserPoolRequest.SetAdminCreateUserConfig(Var_Request.AdminCreateUserConfig.ToAdminCreateUserConfigType());
    for (auto& Group : Var_Request.AutoVerifiedAttributes)
    {
    }
}

void UCreateUserPool_Async::ExecuteFailure(FCognitoError Error)
{
}
