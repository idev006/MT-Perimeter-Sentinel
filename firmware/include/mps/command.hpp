#pragma once
#include <map>
#include <stdexcept>
#include <string>
namespace mps {
class CommandJournal{public: std::string execute_once(const std::string&id,const std::string&payload){auto it=done_.find(id);if(it!=done_.end()){if(it->second.first!=payload)throw std::runtime_error("command id collision");return it->second.second;}std::string result="OK";done_[id]={payload,result};return result;} private:std::map<std::string,std::pair<std::string,std::string>> done_;};
}
