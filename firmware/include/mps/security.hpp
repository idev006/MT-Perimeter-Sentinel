#pragma once
namespace mps {
enum class Role{VIEWER,OPERATOR,ENGINEER,ADMIN,SECURITY_ADMIN};
inline bool authorized(Role r,bool privileged){if(!privileged)return true;return r==Role::ADMIN||r==Role::SECURITY_ADMIN;}
}
