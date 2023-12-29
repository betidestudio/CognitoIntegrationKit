
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "CreateUserPoolDomain_Async.h"

UCreateUserPoolDomain_Async* UCreateUserPoolDomain_Async::CreateUserPoolDomain_Async()
{
    UCreateUserPoolDomain_Async* Node = NewObject<UCreateUserPoolDomain_Async>();
    return Node;
}

void UCreateUserPoolDomain_Async::ContinueProcess(UCIK_Object* CognitoObject)
{
}

void UCreateUserPoolDomain_Async::ExecuteFailure(FCognitoError Error)
{
}
