actions = [
    "AddCustomAttributes", "AdminAddUserToGroup", "AdminConfirmSignUp", "AdminCreateUser",
    "AdminDeleteUser", "AdminDeleteUserAttributes", "AdminDisableProviderForUser", "AdminDisableUser",
    "AdminEnableUser", "AdminForgetDevice", "AdminGetDevice", "AdminGetUser",
    "AdminInitiateAuth", "AdminLinkProviderForUser", "AdminListDevices", "AdminListGroupsForUser",
    "AdminListUserAuthEvents", "AdminRemoveUserFromGroup", "AdminResetUserPassword",
    "AdminRespondToAuthChallenge", "AdminSetUserMFAPreference", "AdminSetUserPassword",
    "AdminSetUserSettings", "AdminUpdateAuthEventFeedback", "AdminUpdateDeviceStatus",
    "AdminUpdateUserAttributes", "AdminUserGlobalSignOut", "AssociateSoftwareToken",
    "ChangePassword", "ConfirmDevice", "ConfirmForgotPassword", "ConfirmSignUp", "CreateGroup",
    "CreateIdentityProvider", "CreateResourceServer", "CreateUserImportJob", "CreateUserPool",
    "CreateUserPoolClient", "CreateUserPoolDomain", "DeleteGroup", "DeleteIdentityProvider",
    "DeleteResourceServer", "DeleteUser", "DeleteUserAttributes", "DeleteUserPool",
    "DeleteUserPoolClient", "DeleteUserPoolDomain", "DescribeIdentityProvider",
    "DescribeResourceServer", "DescribeRiskConfiguration", "DescribeUserImportJob",
    "DescribeUserPool", "DescribeUserPoolClient", "DescribeUserPoolDomain", "ForgetDevice",
    "ForgotPassword", "GetCSVHeader", "GetDevice", "GetGroup", "GetIdentityProviderByIdentifier",
    "GetLogDeliveryConfiguration", "GetSigningCertificate", "GetUICustomization", "GetUser",
    "GetUserAttributeVerificationCode", "GetUserPoolMfaConfig", "GlobalSignOut", "InitiateAuth",
    "ListDevices", "ListGroups", "ListIdentityProviders", "ListResourceServers", "ListTagsForResource",
    "ListUserImportJobs", "ListUserPoolClients", "ListUserPools", "ListUsers", "ListUsersInGroup",
    "ResendConfirmationCode", "RespondToAuthChallenge", "RevokeToken", "SetLogDeliveryConfiguration",
    "SetRiskConfiguration", "SetUICustomization", "SetUserMFAPreference", "SetUserPoolMfaConfig",
    "SetUserSettings", "SignUp", "StartUserImportJob", "StopUserImportJob", "TagResource",
    "UntagResource", "UpdateAuthEventFeedback", "UpdateDeviceStatus", "UpdateGroup",
    "UpdateIdentityProvider", "UpdateResourceServer", "UpdateUserAttributes", "UpdateUserPool",
    "UpdateUserPoolClient", "UpdateUserPoolDomain", "VerifySoftwareToken", "VerifyUserAttribute"
]

header_template = """
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CognitoIntegrationKit/AsyncFunctions/MainClasses/CIKAsyncFunction.h"
#include "{class_name}.generated.h"

/**
 * 
 */
UCLASS()
class COGNITOINTEGRATIONKIT_API U{class_name} : public UCIKAsyncFunction
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"), Category = "Cogntio Integration Kit")
	static U{class_name}* {class_name}();

    virtual void ContinueProcess(UCIK_Object* CognitoObject) override;

	virtual void ExecuteFailure(FCognitoError Error) override;

};
"""

source_template = """
//Copyright (c) 2023 Betide Studio. All Rights Reserved.

#include "{class_name}.h"

U{class_name}* U{class_name}::{class_name}()
{
    U{class_name}* Node = NewObject<U{class_name}>();
    return Node;
}

void U{class_name}::ContinueProcess(UCIK_Object* CognitoObject)
{
}

void U{class_name}::ExecuteFailure(FCognitoError Error)
{
}
"""

for action in actions:
    class_name = action + "_Async"
    header_code = header_template.replace("{class_name}", class_name)
    source_code = source_template.replace("{class_name}", class_name)

    with open(f"{class_name}.h", 'w') as header_file:
        header_file.write(header_code)

    with open(f"{class_name}.cpp", 'w') as source_file:
        source_file.write(source_code)
