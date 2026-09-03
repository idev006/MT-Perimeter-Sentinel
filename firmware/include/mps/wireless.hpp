#pragma once
#include <string>
namespace mps {
class WirelessProfileManager{public: explicit WirelessProfileManager(std::string active):active_(std::move(active)){} const std::string& active()const{return active_;} bool migrate(const std::string& candidate,bool trusted_gateway_ok){if(!trusted_gateway_ok)return false;active_=candidate;return true;} private:std::string active_;};
}
