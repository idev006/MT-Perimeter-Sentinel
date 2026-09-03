#pragma once
#include <string>
namespace mps {
class SafeOta{public: explicit SafeOta(std::string active):active_(std::move(active)){} const std::string& active()const{return active_;} bool install(const std::string& candidate,bool signed_ok,bool self_test_ok){if(!signed_ok||!self_test_ok)return false;previous_=active_;active_=candidate;return true;} bool rollback(){if(previous_.empty())return false;active_=previous_;previous_.clear();return true;} private:std::string active_,previous_;};
}
