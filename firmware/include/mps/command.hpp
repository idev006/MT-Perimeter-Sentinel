#pragma once
#include "security.hpp"
#include <map>
#include <stdexcept>
#include <string>
#include <utility>
#include <vector>

namespace mps {

struct AuditRecord {
  std::string command_id;
  std::string payload;
  std::string result;
  bool replayed{false};
};

class CommandJournal {
 public:
  std::pair<std::string, bool> execute_once_with_status(const std::string& id,
                                                        const std::string& payload) {
    auto it = done_.find(id);
    if (it != done_.end()) {
      if (it->second.first != payload) throw std::runtime_error("command id collision");
      return {it->second.second, true};
    }
    std::string result = "OK";
    done_[id] = {payload, result};
    return {result, false};
  }

  std::string execute_once(const std::string& id, const std::string& payload) {
    return execute_once_with_status(id, payload).first;
  }

 private:
  std::map<std::string, std::pair<std::string, std::string>> done_;
};

class AuditedCommandService {
 public:
  std::string execute(const std::string& id,
                      const std::string& payload,
                      Role role,
                      Action action) {
    if (!authorized(role, action)) {
      audit_.push_back({id, payload, "DENIED", false});
      throw std::runtime_error("command not authorized");
    }
    auto [result, replayed] = journal_.execute_once_with_status(id, payload);
    audit_.push_back({id, payload, result, replayed});
    return result;
  }

  const std::vector<AuditRecord>& audit() const { return audit_; }

 private:
  CommandJournal journal_;
  std::vector<AuditRecord> audit_;
};

}  // namespace mps
