
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "CreateUserPoolClient_Async.h"

UCreateUserPoolClient_Async* UCreateUserPoolClient_Async::CreateUserPoolClient_Async()
{
    UCreateUserPoolClient_Async* Node = NewObject<UCreateUserPoolClient_Async>();
    return Node;
}

void UCreateUserPoolClient_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
}

void UCreateUserPoolClient_Async::ExecuteFailure(FCognitoError Error)
{
}
