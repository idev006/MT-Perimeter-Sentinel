#pragma once
namespace mps {
enum class PowerState{NORMAL,BACKUP,LOW,CRITICAL,OFFLINE};
struct PowerPolicy{static bool allow_detection(PowerState s){return s!=PowerState::OFFLINE;} static bool allow_ota(PowerState s){return s==PowerState::NORMAL;}};
}
